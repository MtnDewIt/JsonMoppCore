/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/Container/Array/hkObjectArray.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

#ifndef HK_MESH_SIMPLIFIER_H
#define HK_MESH_SIMPLIFIER_H

/// A utility for simplifying meshes
/// After the hkQemMeshSimplifier is initialized with an hkQemMutableMesh, edges from the mesh are collapsed,
/// and then edges and faces are patched up.
/// The edges to be collapsed are selected based on a heuristic that attempts to minimize the error introduced to the mesh.
/// Thus, small details like thin triangles or coincident vertices are removed first.
/// This can be a useful tool for generating reduced-complexity physics representations from render meshes

/// NOTES
/// 1)	The algorithm used may end up removing edges that a human might think it shouldn't.
///		You should inspect the output meshes to make sure that no large errors are introduced.
/// 2)	The algorithm is CPU and memory intensive. A large mesh may take several seconds to process.
///		Thus it should NOT be used at runtime.
/// 3)	Materials in the mesh are tracked during simplification, but no attempt is made to avoid merging traingles with
///		different materials. Support for this will be improved in the future.

/// See MeshSimplificationDemo.cpp for more examples on the usage.

struct hkQemPairContraction;
struct hkQemVertexPair;

/// A mesh representation that allows vertices to be remapped to each other
class hkQemMutableMesh
{
public:

	typedef int FaceIndex;
	typedef int VertexIndex;
	typedef hkArray<VertexIndex> VertexList;
	typedef hkArray<FaceIndex> FaceList;
	friend class hkQemMeshSimplifier;

	struct Face
	{
		VertexIndex m_vertexIndices[3];
		
		/// Material ID that is preserved during merges. Defaults to hkUlong(-1)
		hkUlong m_materialId; 
		hkBool m_isValid;

		Face( VertexIndex i, VertexIndex j, VertexIndex k);
		
		// Replaces instances of "from" with "to" and return the # of changed values
		int remapVertices(VertexIndex from, VertexIndex to);
	};

	/// Append the array of vertices to the mesh's vertices. May be called multiple times.
	void addVertices( const hkArray<hkVector4>& verts );

	/// Add a triangle with the specificed vertex indices. The material for the face defaults to hkUlong(-1)
	void addTriangle( VertexIndex i, VertexIndex j, VertexIndex k);

	/// Add a triangle with the specificed vertex indices and material index
	void addTriangleWithMaterial( VertexIndex i, VertexIndex j, VertexIndex k, hkUlong mat);
	
	void validate() const;
	
	/// Approximates the vertex normal based on the surrounding faces.
	void calcVertexNormal( VertexIndex vIdx, hkVector4& normalOut) const;

	/// Computes all the vertex normals using calcVertexNormal
	void getVertexNormals(hkArray<hkVector4>& normals) const;
	
	/// Accessor methods
	const hkArray<hkVector4>& getVertices() const { return m_vertices; }
	const hkArray<Face>& getFaces() const { return m_faces; }


protected:
	void collectEdgeNeighbors(VertexIndex i, VertexIndex j, FaceList& neighbors) const;
	void collectDistanceNeighbors(hkArray<hkQemVertexPair>& neighbors, hkReal tolerance);
	void collectDistanceNeighbors1AxisSweep(hkArray<hkQemVertexPair>& neighbors, hkReal tolerance);
	void collectNormalAndBoundaryEdges(hkArray<hkQemVertexPair>& normal, hkArray<hkQemVertexPair>& boundary) const;
	void pruneDuplicateEdges(hkArray<hkQemVertexPair>& pairs);

	FaceList& getNeighbors(VertexIndex i) { return m_neighorhoods[i]; }
	const FaceList& getNeighbors(VertexIndex i) const { return m_neighorhoods[i]; }

	void computeContraction(VertexIndex v1, VertexIndex v2, hkQemPairContraction& conx, hkVector4Parameter vNew) const;
	int applyContraction(const hkQemPairContraction& conx);

	int unlinkFace(FaceIndex fid);
	// Removes vertices that don't belong to any neighborhoods
	void compact();

	void calcPlaneNormalForFace( FaceIndex fix, hkVector4& planeOut ) const;


protected:
	void getNeighborhoodUnion(VertexIndex i, VertexIndex j, FaceList& un) const;
	void getNeighborhoodIntersection(VertexIndex i, VertexIndex j, FaceList& intersect) const;

	// Returns the "pivot" point - everything from 0..pivot is in neighborhood of vertex i
	int getNeighborhoodSymDifference(VertexIndex i, VertexIndex j, FaceList& symdiff) const;

	static hkBool isSorted(const FaceList& list);

	// Each neighborhood is sorted to make set operations faster
	hkObjectArray< hkArray<FaceIndex> > m_neighorhoods;

	hkArray<hkVector4> m_vertices;
	hkArray<Face> m_faces;
};

struct hkQemPairContraction
{
	typedef int FaceIndex;
	typedef int VertexIndex;
	typedef hkArray<VertexIndex> VertexList;
	typedef hkArray<FaceIndex> FaceList;

	VertexIndex m_v1;
	VertexIndex m_v2;

	hkVector4 m_delta1;
	hkVector4 m_delta2;

	FaceList m_deadFaces;
	// This is how the thesis implements it. Easier with 2 arrays?
	FaceList m_deltaFaces;
	int m_deltaFacesPivot;
};


// Candidates for merging. Not strictly edges in the mesh, can be "close" vertices too
struct hkQemVertexPair
{
	enum PairType
	{
		BOUNDARY_PAIR,	// Special case of an edge pair; an edge only associated with one face
		EDGE_PAIR,		// Edge that existed in the original mesh
		PROXIMITY_PAIR,	// Artificial edge based on vertex proximity
	};
	hkQemMutableMesh::VertexIndex m_v1;
	hkQemMutableMesh::VertexIndex m_v2;
	hkQemMutableMesh::FaceIndex m_faceIndex; // Only used for constraining boundaries
	hkReal m_errorCost; // Used for heap
	int m_heapIndex; // index into heap array
	hkEnum<PairType, hkUint8> m_pairType;
	hkVector4 m_target;

	// Assumes that v1 < v2
	// This is true initially, but may be violated as vertices are remapped
	static hkBool PairIndexLess(const hkQemVertexPair& pairA, const hkQemVertexPair& pairB)
	{
		const hkBool v1LessThan = (pairA.m_v1 < pairB.m_v1);
		const hkBool v1Equals = (pairA.m_v1 == pairB.m_v1);
		const hkBool v2LessThan = (pairA.m_v2 < pairB.m_v2);
		const hkBool v2Equals = (pairA.m_v2 == pairB.m_v2);
		const hkBool typeLessThan = (pairA.m_pairType) < (pairB.m_pairType);
		return v1LessThan || ( v1Equals && v2LessThan ) || (v2Equals && typeLessThan);
	}

	static hkBool ErrorLess(const hkQemVertexPair& pairA, const hkQemVertexPair& pairB)
	{
		return pairA.m_errorCost < pairB.m_errorCost;
	}

	hkBool operator==(const hkQemVertexPair& other)
	{
		return ((m_v1 == other.m_v1) && (m_v2 == other.m_v2))
			|| ((m_v1 == other.m_v2) && (m_v2 == other.m_v1));
	}

	void remap(hkQemMutableMesh::VertexIndex to, hkQemMutableMesh::VertexIndex from)
	{
		HK_ASSERT(0x268f06a3, m_v1 == from || m_v2 == from);
		if (m_v1 == from) { m_v1 = to;}
		if (m_v2 == from) { m_v2 = to;}
	}

	void invalidate()
	{
		m_v1 = -1;
		m_v2 = -1;
	}
};

struct hkQemQuadric
{
public:
	hkMatrix4 m_matrix;

	void initFromPlaneEquation( hkVector4Parameter plane );
	void combineQuadrics( const hkQemQuadric& other, hkQemVertexPair::PairType );
	hkSimdReal calcErrorForVector(hkVector4Parameter v) const;
};


class hkQemMeshSimplifier
{
public:

	enum SimplificationStatus
	{
		STATUS_INVALID,
		
		/// vertices and triangles being passed in
		STATUS_SETUP,
		
		/// simplification started
		STATUS_PROCESSING,
		
		// simplification ended, vertices and triangles are read-only
		STATUS_DONE				
	};

	hkQemMeshSimplifier();
	~hkQemMeshSimplifier();

	typedef int FaceIndex;
	typedef int VertexIndex;
	typedef hkArray<VertexIndex> VertexList;
	typedef hkArray<FaceIndex> FaceList;

	/// Set up the simplifier.
	/// This maps the mesh to a fixed-size AABB
	void initialize( hkQemMutableMesh* mesh );

	/// Remove one edge from the mesh.
	void doSingleContraction();

	/// Removes redundant vertices from the mesh, and remaps the vertices to their original space
	void finalize();

	// Driver routines - removes the specified fraction of vertices or edges from the mesh
	void removeFractionOfVertices(hkReal fract);
	void removeFractionOfFaces(hkReal fract);

	struct Parameters
	{
		/// Vertices closer than distance will be considered as candidates for merging. Set negative to disable.
		hkReal m_vertexMergeDistance;

		/// Weighting applied to boundary edges, making them less likely to be contracted
		hkReal m_boundaryPenalty;

		/// Epsilon value for matrix inversion
		hkReal m_inversionEpsilon;

		/// New vertices are constrained to be within this distance of the segment containing the original vertices
		hkReal m_newVertexMaxDistance;

		/// All vertices are remapped to a cube with extents this size
		hkReal m_remapExtentSize;

		Parameters()
		:	m_vertexMergeDistance(.1f),
			m_boundaryPenalty(10000.0f),
			m_inversionEpsilon(1e-3f),
			m_newVertexMaxDistance(.1f),
			m_remapExtentSize(500.0f)
		{

		}

	};

	Parameters m_params;

protected:
	void constrainBoundaries( hkArray<hkQemVertexPair>& edges, hkReal penalty);
	void processEdges( hkArray<hkQemVertexPair>& edges );
	void computeEdgeInfo( hkQemVertexPair& pair );

	// Removes the pair with lowest cost from the heap, and copies it to pairOut
	void popBestPair(hkQemVertexPair& pairOut);

	void applyContraction(const hkQemPairContraction& contraction, hkQemVertexPair::PairType pairType);
	void remapVerticesInPairs(VertexIndex v1, VertexIndex v2, hkArray<int>& remappedPairs);
	void collectQuadrics();

	void verifyEdges();
	void removeEdgeAt(int removeIndex);

	// Map and unmap vertices to a cube specified by Parameters::m_remapExtentSize
	void mapVertices();
	void unmapVertices();

	struct HeapEntry
	{
		int m_index; // index into pair array
		hkReal m_cost;
	};

	hkArray<HeapEntry> m_heap;
	void heapSwapEntries(int i, int j);
	int heapGetParent(int i) {return (i-1) / 2;}
	int heapGetLeftChild(int i) {return (2*i + 1);}
	int heapGetRightChild(int i) {return (2*i + 2);}
	int heapGetSmallerChild(int i);
	void heapDeleteEntry(int i);

	void upHeap(int i);
	void downHeap(int i);

	void verifyHeap();

public:
	hkQemMutableMesh* m_mesh;
	// These decrease as we contract vertex pairs
	int m_numFaces;
	int m_numVertices;

protected:
	hkArray<hkQemQuadric> m_quadrics;
	hkObjectArray< hkArray<int> > m_edgeMapping;

	hkEnum<SimplificationStatus, hkUint8> m_status;
	hkAabb m_originalAabb;

	hkArray<hkQemVertexPair> m_pairs;
};

#endif // HK_MESH_SIMPLIFIER_H

/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20090216)
* 
* Confidential Information of Havok.  (C) Copyright 1999-2009
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
* 
* Use of this software for evaluation purposes is subject to and indicates
* acceptance of the End User licence Agreement for this product. A copy of
* the license is included with this software and is also available at www.havok.com/tryhavok.
* 
*/
