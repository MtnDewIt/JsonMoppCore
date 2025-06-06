/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// Autogenerated by genRegister.py

#include <Physics/Collide/Agent/Collidable/hkpCdBodyClass.cpp>
#include <Physics/Collide/Agent/Collidable/hkpCollidableClass.cpp>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandleClass.cpp>
#include <Physics/Collide/Filter/DefaultConvexList/hkpDefaultConvexListFilterClass.cpp>
#include <Physics/Collide/Filter/Group/hkpGroupFilterClass.cpp>
#include <Physics/Collide/Filter/List/hkpCollisionFilterListClass.cpp>
#include <Physics/Collide/Filter/Null/hkpNullCollisionFilterClass.cpp>
#include <Physics/Collide/Filter/hkpCollidableCollidableFilterClass.cpp>
#include <Physics/Collide/Filter/hkpCollisionFilterClass.cpp>
#include <Physics/Collide/Filter/hkpConvexListFilterClass.cpp>
#include <Physics/Collide/Filter/hkpRayCollidableFilterClass.cpp>
#include <Physics/Collide/Filter/hkpShapeCollectionFilterClass.cpp>
#include <Physics/Collide/Shape/Compound/Collection/ExtendedMeshShape/hkpExtendedMeshShapeClass.cpp>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShapeClass.cpp>
#include <Physics/Collide/Shape/Compound/Collection/Mesh/hkpMeshMaterialClass.cpp>
#include <Physics/Collide/Shape/Compound/Collection/SimpleMesh/hkpSimpleMeshShapeClass.cpp>
#include <Physics/Collide/Shape/Compound/Collection/StorageExtendedMesh/hkpStorageExtendedMeshShapeClass.cpp>
#include <Physics/Collide/Shape/Compound/Collection/hkpShapeCollectionClass.cpp>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/Modifiers/hkpRemoveTerminalsMoppModifierClass.cpp>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShapeClass.cpp>
#include <Physics/Collide/Shape/Compound/Tree/hkpBvTreeShapeClass.cpp>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShapeClass.cpp>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShapeClass.cpp>
#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShapeClass.cpp>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShapeClass.cpp>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesConnectivityClass.cpp>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShapeClass.cpp>
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShapeClass.cpp>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShapeClass.cpp>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShapeClass.cpp>
#include <Physics/Collide/Shape/Convex/hkpConvexShapeClass.cpp>
#include <Physics/Collide/Shape/Deprecated/ConvexPieceMesh/hkpConvexPieceMeshShapeClass.cpp>
#include <Physics/Collide/Shape/Deprecated/FastMesh/hkpFastMeshShapeClass.cpp>
#include <Physics/Collide/Shape/Deprecated/Mesh/hkpMeshShapeClass.cpp>
#include <Physics/Collide/Shape/Deprecated/MultiSphere/hkpMultiSphereShapeClass.cpp>
#include <Physics/Collide/Shape/Deprecated/StorageMesh/hkpStorageMeshShapeClass.cpp>
#include <Physics/Collide/Shape/HeightField/CompressedSampledHeightField/hkpCompressedSampledHeightFieldShapeClass.cpp>
#include <Physics/Collide/Shape/HeightField/Plane/hkpPlaneShapeClass.cpp>
#include <Physics/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShapeClass.cpp>
#include <Physics/Collide/Shape/HeightField/StorageSampledHeightField/hkpStorageSampledHeightFieldShapeClass.cpp>
#include <Physics/Collide/Shape/HeightField/TriSampledHeightField/hkpTriSampledHeightFieldBvTreeShapeClass.cpp>
#include <Physics/Collide/Shape/HeightField/TriSampledHeightField/hkpTriSampledHeightFieldCollectionClass.cpp>
#include <Physics/Collide/Shape/HeightField/hkpHeightFieldShapeClass.cpp>
#include <Physics/Collide/Shape/HeightField/hkpSphereRepShapeClass.cpp>
#include <Physics/Collide/Shape/Misc/Bv/hkpBvShapeClass.cpp>
#include <Physics/Collide/Shape/Misc/ConvexList/hkpConvexListShapeClass.cpp>
#include <Physics/Collide/Shape/Misc/MultiRay/hkpMultiRayShapeClass.cpp>
#include <Physics/Collide/Shape/Misc/PhantomCallback/hkpPhantomCallbackShapeClass.cpp>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShapeClass.cpp>
#include <Physics/Collide/Shape/Query/hkpRayShapeCollectionFilterClass.cpp>
#include <Physics/Collide/Shape/Query/hkpShapeRayBundleCastInputClass.cpp>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastInputClass.cpp>
#include <Physics/Collide/Shape/hkpShapeClass.cpp>
#include <Physics/Collide/Shape/hkpShapeContainerClass.cpp>
#include <Physics/Collide/Util/ShapeInfo/hkpShapeInfoClass.cpp>
#include <Physics/Collide/Util/Welding/hkpWeldingUtilityClass.cpp>

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
