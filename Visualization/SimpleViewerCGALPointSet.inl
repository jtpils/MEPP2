// Copyright (c) 2012-2019 University of Lyon and CNRS (France).
// All rights reserved.
//
// This file is part of MEPP2; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

#include "FEVV/DataStructures/DataStructures_cgal_point_set.h"
#include "FEVV/Wrappings/Graph_properties_cgal_point_set.h"


namespace FEVV {

//
// SimpleViewer<>::internal_createMesh(...) specialization for FEVV::CGALPointSet
// with  HalfedgeGraph = FEVV::CGALPointSet and PointMap = FEVV::CGALPointSet
//
template<>
inline void
SimpleViewer::internal_createMesh< FEVV::CGALPointSet,
                                   FEVV::CGALPointSetPointMap >(
    osg::Geode *&geode,
    FEVV::CGALPointSet *_g,
    PMapsContainer *_pmaps,
    std::vector< osg::ref_ptr< osg::Geometry > > &geometries,
    std::vector< osg::ref_ptr< osg::Geometry > > &geometriesL,
    std::vector< osg::ref_ptr< osg::Geometry > > &geometriesP,
    std::vector< osg::ref_ptr< osg::Geometry > > &geometries_edges,
    std::vector< osg::ref_ptr< osg::Geometry > > &geometries_vertices,
    std::vector< osg::ref_ptr< osg::Vec3Array > > &vertexArrays,
    std::vector< osg::ref_ptr< osg::Vec3Array > > &vertexArrays_edges,
    std::vector< osg::ref_ptr< osg::Vec3Array > > &vertexArrays_vertices,
    std::vector< osg::ref_ptr< osg::Vec3Array > > &normalsArrays,
    std::vector< osg::ref_ptr< osg::Vec3Array > > &normalsArraysF,
    std::vector< osg::ref_ptr< osg::Vec3Array > > &normalsArrays_vertices,
    std::vector< osg::ref_ptr< osg::Vec3Array > > &tangentsArrays,
    std::vector< osg::ref_ptr< osg::Vec4Array > > &colorsArrays,
    std::vector< osg::ref_ptr< osg::Vec4Array > > &colorsArrays_edges,
    std::vector< osg::ref_ptr< osg::Vec4Array > > &colorsArrays_vertices,
    std::vector< osg::ref_ptr< osg::Vec2Array > > &texcoordsArrays,
    FEVV::CGALPointSetPointMap *_pm,
    std::string _mesh_file)
{
  internal_createMesh_pointcloud(geode,
                                 _g,
                                 _pmaps,
                                 geometries,
                                 geometriesL,
                                 geometriesP,
                                 geometries_edges,
                                 geometries_vertices,
                                 vertexArrays,
                                 vertexArrays_edges,
                                 vertexArrays_vertices,
                                 normalsArrays,
                                 normalsArraysF,
                                 normalsArrays_vertices,
                                 tangentsArrays,
                                 colorsArrays,
                                 colorsArrays_edges,
                                 colorsArrays_vertices,
                                 texcoordsArrays,
                                 _pm,
                                 _mesh_file);
}

} // namespace FEVV