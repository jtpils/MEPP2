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
#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>

#include "FEVV/Wrappings/Geometry_traits_cgal_polyhedron_3.h" // Geometry adaptor

//#define USE_GENERIC_READER_WRITER // when activated you need to link to vtk
//libs if VTK is used
#ifdef USE_GENERIC_READER_WRITER
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>

#include "FEVV/Wrappings/Graph_traits_extension_cgal_polyhedron_3.h"
#include "FEVV/Wrappings/properties_cgal.h"
#include "FEVV/Filters/Generic/generic_reader.hpp"
#include "FEVV/Filters/Generic/generic_writer.hpp"
#endif

#include "FEVV/Tools/IO/FileUtilities.hpp"

#include "FEVV/Filters/Generic/Manifold/calculate_vertices_one_ring_barycenter.hpp"
#include "FEVV/Filters/Generic/Manifold/calculate_vertices_one_ring_angles_based_centroid.hpp"
#include "FEVV/Filters/Generic/Manifold/calculate_vertices_one_ring_geometric_laplacian.hpp"
#include "FEVV/Filters/Generic/reposition_vertices.hpp"

#include <fstream>
#include <string>

using namespace FEVV;
using namespace FEVV::Filters;

void
test_smoothing_polyhedron(std::string filename)
{
  typedef CGAL::Cartesian< double > Kernel;
  typedef CGAL::Polyhedron_3< Kernel, CGAL::Polyhedron_items_with_id_3 > Mesh;

  typedef boost::graph_traits< Mesh > GraphTraits;
  typedef typename GraphTraits::vertex_descriptor vertex_descriptor;
  typedef typename GraphTraits::vertex_iterator vertex_iterator;

  typedef FEVV::Geometry_traits< Mesh > Geometry;
  typedef Geometry::Point Point;
  typedef boost::vector_property_map<
      Point,
      typename boost::property_map< Mesh, boost::vertex_index_t >::const_type >
      BarycenterMap;
  /**********************************************************************************************************/
  Mesh m;
#ifdef USE_GENERIC_READER_WRITER
  FEVV::PMapsContainer pmaps;
  FEVV::Filters::read_mesh(filename, m, pmaps);
#else
  std::ifstream in(filename);
  if(!in)
  {
    std::cerr << "Unable to read file " << filename << std::endl;
    exit(EXIT_FAILURE);
  }
  in >> m;
#endif
  /**********************************************************************************************************/
  vertex_iterator vb, ve;
  int index = 0;
  for(boost::tie(vb, ve) = boost::vertices(m); vb != ve; ++vb)
  {
    vertex_descriptor vd = *vb;
    vd->id() = index++; // When using a Polyhedron with indices you need to
                        // initialize the indices manually
  }
  /**********************************************************************************************************/
  auto pos_pm = get(boost::vertex_point, m);
  /**********************************************************************************************************/
  BarycenterMap barycenters_pm(get(boost::vertex_index, m));
  FEVV::Filters::calculate_vertices_one_ring_barycenter(
      m, pos_pm, barycenters_pm, 0.2f);
  FEVV::Filters::reposition_vertices(m, pos_pm, barycenters_pm);

  FEVV::Filters::calculate_vertices_one_ring_angles_based_centroid(
      m, pos_pm, barycenters_pm, 0.2f);
  FEVV::Filters::reposition_vertices(m, pos_pm, barycenters_pm);

  FEVV::Filters::calculate_vertices_one_ring_geometric_laplacian(
      m, pos_pm, barycenters_pm, 0.2f);
  FEVV::Filters::reposition_vertices(m, pos_pm, barycenters_pm);
  /**********************************************************************************************************/
#ifdef USE_GENERIC_READER_WRITER
  FEVV::Filters::write_mesh("smoothed_poly_" +
                                FEVV::FileUtils::get_file_name(filename) +
                                FEVV::FileUtils::get_file_extension(filename),
                            m,
                            pmaps);
#else
  std::ofstream smoothed_off("smoothed_poly_" +
                             FEVV::FileUtils::get_file_name(filename) +
                             FEVV::FileUtils::get_file_extension(filename));
  smoothed_off << m;
  smoothed_off.close();
#endif

  std::cout << "Done." << std::endl;
}

int
main(int narg, char **argv)
{
  if(narg < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " filename; filename being an off file." << std::endl;
    exit(EXIT_FAILURE);
  }

  test_smoothing_polyhedron(argv[1]);

  // system("pause");
  return 0;
}
