#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "teaserpp::teaser_io" for configuration "Release"
set_property(TARGET teaserpp::teaser_io APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(teaserpp::teaser_io PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/teaser_io.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "tinyply"
  )

list(APPEND _IMPORT_CHECK_TARGETS teaserpp::teaser_io )
list(APPEND _IMPORT_CHECK_FILES_FOR_teaserpp::teaser_io "${_IMPORT_PREFIX}/lib/teaser_io.lib" )

# Import target "teaserpp::teaser_registration" for configuration "Release"
set_property(TARGET teaserpp::teaser_registration APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(teaserpp::teaser_registration PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/teaser_registration.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "pmc::pmc"
  )

list(APPEND _IMPORT_CHECK_TARGETS teaserpp::teaser_registration )
list(APPEND _IMPORT_CHECK_FILES_FOR_teaserpp::teaser_registration "${_IMPORT_PREFIX}/lib/teaser_registration.lib" )

# Import target "teaserpp::teaser_features" for configuration "Release"
set_property(TARGET teaserpp::teaser_features APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(teaserpp::teaser_features PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/teaser_features.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "pcl_common;pcl_kdtree;pcl_octree;pcl_search;pcl_sample_consensus;pcl_filters;pcl_io;pcl_features;pcl_ml;pcl_segmentation;pcl_visualization;pcl_surface;pcl_registration;pcl_keypoints;pcl_tracking;pcl_recognition;pcl_stereo;pcl_outofcore;pcl_people;vtkChartsCore;vtkCommonColor;vtkCommonCore;vtksys;vtkCommonDataModel;vtkCommonMath;vtkCommonMisc;vtkCommonSystem;vtkCommonTransforms;vtkCommonExecutionModel;vtkFiltersGeneral;vtkCommonComputationalGeometry;vtkFiltersCore;vtkInfovisCore;vtkFiltersExtraction;vtkFiltersStatistics;vtkImagingFourier;vtkImagingCore;vtkRenderingContext2D;vtkRenderingCore;vtkFiltersGeometry;vtkFiltersSources;vtkRenderingFreeType;vtkfreetype;vtkzlib;vtkFiltersModeling;vtkImagingSources;vtkInteractionStyle;vtkInteractionWidgets;vtkFiltersHybrid;vtkImagingColor;vtkImagingGeneral;vtkImagingHybrid;vtkIOImage;vtkDICOMParser;vtkmetaio;vtkjpeg;vtkpng;vtktiff;vtkRenderingAnnotation;vtkRenderingVolume;vtkIOXML;vtkIOCore;vtkdoubleconversion;vtklz4;vtklzma;vtkIOXMLParser;vtkexpat;vtkIOGeometry;vtkIOLegacy;vtkIOPLY;vtkRenderingLOD;vtkViewsContext2D;vtkViewsCore;vtkRenderingContextOpenGL2;vtkRenderingOpenGL2;vtkglew"
  )

list(APPEND _IMPORT_CHECK_TARGETS teaserpp::teaser_features )
list(APPEND _IMPORT_CHECK_FILES_FOR_teaserpp::teaser_features "${_IMPORT_PREFIX}/lib/teaser_features.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
