/* === S Y N F I G ========================================================= */
/*!	\file valuenode_vectory.cpp
**	\brief Implementation of the "Vector Y" valuenode conversion.
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2007, 2008 Chris Moore
**  Copyright (c) 2011 Carlos López
**
**	This file is part of Synfig.
**
**	Synfig is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 2 of the License, or
**	(at your option) any later version.
**
**	Synfig is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with Synfig.  If not, see <https://www.gnu.org/licenses/>.
**	\endlegal
*/
/* ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include "valuenode_vectory.h"
#include "valuenode_const.h"
#include <synfig/general.h>
#include <synfig/localization.h>
#include <synfig/valuenode_registry.h>
#include <synfig/vector.h>

#endif

/* === U S I N G =========================================================== */

using namespace synfig;

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

REGISTER_VALUENODE(ValueNode_VectorY, RELEASE_VERSION_0_61_09, "vectory", N_("Vector Y"))

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

ValueNode_VectorY::ValueNode_VectorY(const ValueBase &value):
	LinkableValueNode(value.get_type())
{
	Vocab ret(get_children_vocab());
	set_children_vocab(ret);
	if (value.get_type() == type_real)
		set_link("vector",ValueNode_Const::create(Vector(0, value.get(Real()))));
	else
		throw Exception::BadType(value.get_type().description.local_name);
}

LinkableValueNode*
ValueNode_VectorY::create_new()const
{
	return new ValueNode_VectorY(get_type());
}

ValueNode_VectorY*
ValueNode_VectorY::create(const ValueBase& x, etl::loose_handle<Canvas>)
{
	return new ValueNode_VectorY(x);
}

ValueNode_VectorY::~ValueNode_VectorY()
{
	unlink_all();
}

ValueBase
ValueNode_VectorY::operator()(Time t)const
{
	DEBUG_LOG("SYNFIG_DEBUG_VALUENODE_OPERATORS",
		"%s:%d operator()\n", __FILE__, __LINE__);

	return (*vector_)(t).get(Vector())[1];
}


bool
ValueNode_VectorY::set_link_vfunc(int i,ValueNode::Handle value)
{
	assert(i>=0 && i<link_count());

	switch(i)
	{
	case 0: CHECK_TYPE_AND_SET_VALUE(vector_, type_vector);
	}
	return false;
}

ValueNode::LooseHandle
ValueNode_VectorY::get_link_vfunc(int i)const
{
	assert(i>=0 && i<link_count());

	if(i==0)
		return vector_;
	return 0;
}



bool
ValueNode_VectorY::check_type(Type &type)
{
	return type==type_real;
}

LinkableValueNode::Vocab
ValueNode_VectorY::get_children_vocab_vfunc()const
{
	if(children_vocab.size())
		return children_vocab;

	LinkableValueNode::Vocab ret;

	ret.push_back(ParamDesc(ValueBase(),"vector")
		.set_local_name(_("Vector"))
		.set_description(_("The vector where the Y coordinate is extracted from"))
	);

	return ret;
}
