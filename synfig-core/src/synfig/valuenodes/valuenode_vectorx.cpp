/* === S Y N F I G ========================================================= */
/*!	\file valuenode_vectorx.cpp
**	\brief Implementation of the "Vector X" valuenode conversion.
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

#include "valuenode_vectorx.h"
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

REGISTER_VALUENODE(ValueNode_VectorX, RELEASE_VERSION_0_61_09, "vectorx", N_("Vector X"))

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

ValueNode_VectorX::ValueNode_VectorX(const ValueBase &value):
	LinkableValueNode(value.get_type())
{
	Vocab ret(get_children_vocab());
	set_children_vocab(ret);
	if (value.get_type() == type_real)
		set_link("vector",ValueNode_Const::create(Vector(value.get(Real()), 0)));
	else
		throw Exception::BadType(value.get_type().description.local_name);
}

LinkableValueNode*
ValueNode_VectorX::create_new()const
{
	return new ValueNode_VectorX(get_type());
}

ValueNode_VectorX*
ValueNode_VectorX::create(const ValueBase& x, etl::loose_handle<Canvas>)
{
	return new ValueNode_VectorX(x);
}

ValueNode_VectorX::~ValueNode_VectorX()
{
	unlink_all();
}

ValueBase
ValueNode_VectorX::operator()(Time t)const
{
	DEBUG_LOG("SYNFIG_DEBUG_VALUENODE_OPERATORS",
		"%s:%d operator()\n", __FILE__, __LINE__);

	return (*vector_)(t).get(Vector())[0];
}


bool
ValueNode_VectorX::set_link_vfunc(int i,ValueNode::Handle value)
{
	assert(i>=0 && i<link_count());

	switch(i)
	{
	case 0: CHECK_TYPE_AND_SET_VALUE(vector_, type_vector);
	}
	return false;
}

ValueNode::LooseHandle
ValueNode_VectorX::get_link_vfunc(int i)const
{
	assert(i>=0 && i<link_count());

	if(i==0)
		return vector_;
	return 0;
}



bool
ValueNode_VectorX::check_type(Type &type)
{
	return type==type_real;
}

LinkableValueNode::Vocab
ValueNode_VectorX::get_children_vocab_vfunc()const
{
	if(children_vocab.size())
		return children_vocab;

	LinkableValueNode::Vocab ret;

	ret.push_back(ParamDesc(ValueBase(),"vector")
		.set_local_name(_("Vector"))
		.set_description(_("The vector where the X coordinate is extracted from"))
	);

	return ret;
}
