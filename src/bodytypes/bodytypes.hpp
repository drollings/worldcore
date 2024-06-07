#ifndef __BODYTYPES_HPP__
#define __BODYTYPES_HPP__

//
// C++ Interface: bodytypes
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "base.hpp"
#include "property.hpp"
#include "Templates/SharedPtr.hpp"

namespace BodyTypes
{
	class Body;
}

// A body should contain a vector of the items it wears, and what they cover at what layer
/*

    {  0, 1, 0, 60, WEAR_MSG_HELDIN, HOLDING_SOMETHING_IN, (ITEM_WEAR_TAKE | ITEM_WEAR_SHIELD | ITEM_WEAR_WIELD), "hand", "primary" },
    {  6, 1, 0, 50, WEAR_MSG_WEARAROUND, WEARING_SOMETHING_AROUND, ITEM_WEAR_WRIST, "right wrist", "r-wrist" },
    {  0, 1, 0, 20, WEAR_MSG_SLIDEONTO, WEARING_SOMETHING_AROUND, ITEM_WEAR_FINGER, "right ring finger", "r-finger" },


    {  0, 1, 0, 20, WEAR_MSG_SLIDEONTO, WEARING_SOMETHING_AROUND, ITEM_WEAR_FINGER, "right ring finger", "r-finger" },
    {  0, 1, 0, 20, WEAR_MSG_SLIDEONTO, WEARING_SOMETHING_AROUND, ITEM_WEAR_FINGER, "left ring finger", "l-finger" },
    { -1, 1, 0, 100, 0, 0, 0, "", "" },
    { -1, 1, 0, 100, 0, 0, 0, "", "" },
    {  2, 4, 0, 100, WEAR_MSG_WEARAROUND, WEAR_ANYTHING_ELSE, ITEM_WEAR_NECK, "neck", "neck" },
    {  2, 4, 0, 100, WEAR_MSG_WEARAROUND, WEAR_ANYTHING_ELSE, ITEM_WEAR_NECK, "neck", "neck" },
    {  8, 3, 0, 100, WEAR_MSG_WEARON, WEARING_SOMETHING_ON, ITEM_WEAR_BODY, "body", "body" },
    {  3, 2, 2, 100, WEAR_MSG_WEARON, WEARING_SOMETHING_ON, ITEM_WEAR_HEAD, "head", "head" },
    {  3, 2, 0, 100, WEAR_MSG_WEARON, WEARING_SOMETHING_ON, ITEM_WEAR_FACE, "face", "face" },
    {  3, 4, 0, 100, WEAR_MSG_WEAROVER, WEARING_SOMETHING_OVER, ITEM_WEAR_EYES, "eyes", "eyes" },
    {  0, 1, 0, 20, WEAR_MSG_PUTON, WEARING_SOMETHING_ON, ITEM_WEAR_EAR, "right ear", "r-ear" },
    {  0, 1, 0, 20, WEAR_MSG_PUTON, WEARING_SOMETHING_ON, ITEM_WEAR_EAR, "left ear", "l-ear" },
    { 11, 1, 0, 60, WEAR_MSG_WEARON, WEARING_SOMETHING_ON, ITEM_WEAR_LEGS, "legs", "legs" },
    { 12, 1, 0, 40, WEAR_MSG_WEARON, WEARING_SOMETHING_ON, ITEM_WEAR_FEET, "feet", "feet" },
    {  5, 1, 0, 30, WEAR_MSG_WEARON, WEARING_SOMETHING_ON, ITEM_WEAR_HANDS, "hands", "hands" },
    {  0, 3, 0, 100, WEAR_MSG_SLUNGOVER, WEARING_SOMETHING_OVER, ITEM_WEAR_SHOULDER, "shoulder", "shoulder" },
    {  4, 1, 0, 40, WEAR_MSG_WEARON, WEARING_SOMETHING_ON, ITEM_WEAR_ARMS, "arms", "arms" },
    { 10, 3, 0, 100, WEAR_MSG_WEARABOUT, WEARING_SOMETHING_AROUND, ITEM_WEAR_WAIST, "waist", "waist" },
    {  7, 3, 0, 100, WEAR_MSG_WEARABOUT, WEARING_SOMETHING_ABOUT, ITEM_WEAR_ABOUT, "body", "about" },
    {  0, 3, 0, 100, WEAR_MSG_STRAPTO, WEARING_SOMETHING_ON, ITEM_WEAR_BACK, "back", "back" },
    {  0, 2, 0, 100, WEAR_MSG_WEARFROM, WEARING_SOMETHING_ON, ITEM_WEAR_ONBELT, "waist", "fromwaist" },
    {  0, 2, 0, 100, WEAR_MSG_WEARFROM, WEARING_SOMETHING_ON, ITEM_WEAR_ONBELT, "waist", "fromwaist" },
    {  6, 1, 0, 50, WEAR_MSG_WEARAROUND, WEARING_SOMETHING_AROUND, ITEM_WEAR_WRIST, "right wrist", "r-wrist" },
    {  9, 1, 0, 50, WEAR_MSG_WEARAROUND, WEARING_SOMETHING_AROUND, ITEM_WEAR_WRIST, "left wrist", "l-wrist" },
    { -1, 1, 0, 100, 0, 0, 0, "", "" },
    { -1, 1, 0, 100, 0, 0, 0, "", "" },
    {  0, 1, 0, 60, WEAR_MSG_HELDIN, HOLDING_SOMETHING_IN, (ITEM_WEAR_TAKE | ITEM_WEAR_SHIELD | ITEM_WEAR_WIELD), "hand", "primary" },
    {  0, 1, 0, 60, WEAR_MSG_HELDIN, HOLDING_SOMETHING_IN, (ITEM_WEAR_TAKE | ITEM_WEAR_SHIELD | ITEM_WEAR_WIELD), "hand", "off" },
    { -1, 1, 0, 100, 0, 0, 0, "", "" },
    { -1, 1, 0, 100, 0, 0, 0, "", "" }
                    
*/



namespace Property
{
	class BodyType : public Property, public Base::Holds
	{
	public:
		PROPERTY_DECLARE(BodyType);
	
	private:
        // Lexi::SharedPtr<::BodyTypes::BodyType>		m_pBodyType;

        Flags			m_Injured;
        Flags			m_Crippled;
        Flags			m_Lost;
        
    public:	
		ElementList		m_lEquipment;

        const ::BodyTypes::Body *	GetBodyType(void) const;
        void						SetBodyType(const ::BodyTypes::Body *pBody);
	};
}


#endif	// __BODYTYPES_HPP__
