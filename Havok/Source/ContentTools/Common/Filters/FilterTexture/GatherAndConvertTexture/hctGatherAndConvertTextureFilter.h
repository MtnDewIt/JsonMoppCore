/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HAVOK_FILTER_TEXTURES_GATHER_AND_CONVERT__H
#define HAVOK_FILTER_TEXTURES_GATHER_AND_CONVERT__H

#include <ContentTools/Common/Filters/FilterTexture/GatherAndConvertTexture/hctGatherAndConvertTextureFilterOptions.h>

class hctGatherAndConvertTextureFilter : public hctFilterInterface
{
	public: 

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT);

		hctGatherAndConvertTextureFilter(const hctFilterManagerInterface* owner);
		/*virtual*/ ~hctGatherAndConvertTextureFilter();

		/*virtual*/ void setOptions(const void* optionData, int optionDataSize, unsigned int version);
		/*virtual*/ HWND showOptions(HWND owner);

		/*virtual*/ void process( class hkRootLevelContainer& data );

		/// Option ptr only valid until the filter is deleted and/or the filter dll is unloaded
		/*virtual*/ int getOptionsSize() const;
		/*virtual*/ void getOptions(void* optionData) const;

		virtual void hideOptions();

		void updateOptions();
		
		// filter options
		hctGatherAndConvertTextureFilterOptions m_options;
		hkObjectArray< hkString > m_nameStrings;
		hkArray< hkxTextureFile* > m_listedFileTextures;
		hkArray< hkxTextureInplace* > m_listedInplaceTextures;
		hkArray< int > m_currentEditOptionIndices;

		hkRootLevelContainer* m_optionSceneData; 
		hctFilterMemoryTracker m_optionSceneDataTracker;

		// A buffer for storing the options in XML form.
		mutable hkArray<char> m_getOptionsBuf;
		mutable hkArray<char> m_setOptionsBuf;

		// dialog
		HWND m_optionsDialog;	
};

class hctGatherAndConvertTextureFilterDesc : public hctFilterDescriptor
{
	public:

		/*virtual*/ unsigned int getID() const { return 0x7382abaa; }
		/*virtual*/ FilterCategory getCategory() const { return HK_CATEGORY_GRAPHICS; }
		/*virtual*/ FilterBehaviour getFilterBehaviour() const { return HK_DATA_MUTATES_INPLACE; }
		/*virtual*/ const char* getShortName() const { return "GatherAndConvertTextures"; }
		/*virtual*/ const char* getLongName() const { return "Convert textures using FreeImage (so a lot of file types supported). Creates new file or new inplace texture depending on input."; }
		/*virtual*/ unsigned int getFilterVersion() const { return HCT_FILTER_VERSION(1,1,1); }
		/*virtual*/ hctFilterInterface* createFilter(const hctFilterManagerInterface* owner) const { return new hctGatherAndConvertTextureFilter(owner); }

		/*virtual*/ HavokComponentMask getRequiredHavokComponents () const { return HK_COMPONENT_COMMON; }
};

extern hctGatherAndConvertTextureFilterDesc g_gatherAndConvertTextureDesc;

#endif // HAVOK_FILTER_TEXTURES_GATHER_AND_CONVERT__H

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
