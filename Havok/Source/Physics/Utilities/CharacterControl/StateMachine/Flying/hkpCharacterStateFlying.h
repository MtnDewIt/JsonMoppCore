/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_CHARACTER_STATE_FLYING
#define HK_CHARACTER_STATE_FLYING

#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>

/// A state to represent flying.
/// This state is currently unused - no other states transition to it.
class hkpCharacterStateFlying : public hkpCharacterState
{
	public:

		hkpCharacterStateFlying() {}

			/// Return the state type
		virtual hkpCharacterStateType getType() const;

		/// Process the user input - causes state actions.
		virtual void update(hkpCharacterContext& context, const hkpCharacterInput& input, hkpCharacterOutput& output);

		///	Process the user input - causes state transitions.		
		virtual void change(hkpCharacterContext& context, const hkpCharacterInput& input, hkpCharacterOutput& output);
};

#endif // HK_CHARACTER_STATE_FLYING

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
