/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */




void hkpCylinderShape::setVertex(int i, const hkVector4& position )
{
	HK_ASSERT2(0x4d78b768,  i>=0 && i < 2, "A cylinder has only 2 vertices. getVertex() must be passed either 0 or 1. ");
	(&m_vertexA)[i] = position;
}


const hkVector4* hkpCylinderShape::getVertices() const
{
	return &m_vertexA;
}

const hkVector4& hkpCylinderShape::getVertex(int i) const
{
	HK_ASSERT2(0x5e57e9fc,  i>=0 && i < 2, "A cylinder has only 2 vertices. getVertex() must be passed either 0 or 1. ");
	return (getVertices())[i];
}

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
