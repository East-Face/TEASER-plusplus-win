// An example showing TEASER++ registration with FPFH features with the Stanford bunny model
#include <chrono>
#include <iostream>
#include <random>

#include <Eigen/Core>

#include <teaser/ply_io.h>
#include <teaser/registration.h>
#include <teaser/matcher.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/transforms.h>

// Macro constants for generating noise and outliers
#define NOISE_BOUND 0.001
#define N_OUTLIERS 1700
#define OUTLIER_TRANSLATION_LB 5
#define OUTLIER_TRANSLATION_UB 10

inline double getAngularError(Eigen::Matrix3d R_exp, Eigen::Matrix3d R_est) {
  return std::abs(std::acos(fmin(fmax(((R_exp.transpose() * R_est).trace() - 1) / 2, -1.0), 1.0)));
}

//void addNoiseAndOutliers(Eigen::Matrix<double, 3, Eigen::Dynamic>& tgt) {
//  // Add uniform noise
//  Eigen::Matrix<double, 3, Eigen::Dynamic> noise =
//      Eigen::Matrix<double, 3, Eigen::Dynamic>::Random(3, tgt.cols()) * NOISE_BOUND / 2;
//  tgt = tgt + noise;
//
//  // Add outliers
//  std::random_device rd;
//  std::mt19937 gen(rd());
//  std::uniform_int_distribution<> dis2(0, tgt.cols() - 1); // pos of outliers
//  std::uniform_int_distribution<> dis3(OUTLIER_TRANSLATION_LB,
//                                       OUTLIER_TRANSLATION_UB); // random translation
//  std::vector<bool> expected_outlier_mask(tgt.cols(), false);
//  for (int i = 0; i < N_OUTLIERS; ++i) {
//    int c_outlier_idx = dis2(gen);
//    assert(c_outlier_idx < expected_outlier_mask.size());
//    expected_outlier_mask[c_outlier_idx] = true;
//    tgt.col(c_outlier_idx).array() += dis3(gen); // random translation
//  }
//}
pcl::PointCloud<pcl::PointXYZ>::Ptr
CloudPreprocessor(pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud, float rate) {
  pcl::PointCloud<pcl::PointXYZ>::Ptr target(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::transformPointCloud<pcl::PointXYZ>(
      *source_cloud, *target, Eigen::Affine3f(Eigen::UniformScaling<float>((float)0.001)));

  target->erase(std::remove_if(target->begin(), target->end(),
                               [=](const pcl::PointXYZ& pt) {
                                 return pt.getVector3fMap().squaredNorm() < 1e-12;
                               }),
                target->end());

  // downsampling
  pcl::ApproximateVoxelGrid<pcl::PointXYZ> voxelgrid;
  voxelgrid.setLeafSize(rate, rate, rate);

  pcl::PointCloud<pcl::PointXYZ>::Ptr filtered(new pcl::PointCloud<pcl::PointXYZ>());
  voxelgrid.setInputCloud(target);
  voxelgrid.filter(*filtered);
  target = filtered;

  std::vector<int> mapping;
  pcl::removeNaNFromPointCloud(*target, *target, mapping);
  //µ„‘∆π˝¬À
  // SORFilter(target, target, 30, 2.0);

  return target;
}

int main() {
  // Load the .ply file
  //teaser::PLYReader reader;
  //teaser::PointCloud src_cloud;
  //auto status = reader.read("./example_data/bun_zipper_res3.ply", src_cloud);
  //int N = src_cloud.size();

  //// Convert the point cloud to Eigen
  //Eigen::Matrix<double, 3, Eigen::Dynamic> src(3, N);
  //for (size_t i = 0; i < N; ++i) {
  //  src.col(i) << src_cloud[i].x, src_cloud[i].y, src_cloud[i].z;
  //}

  //// Homogeneous coordinates
  //Eigen::Matrix<double, 4, Eigen::Dynamic> src_h;
  //src_h.resize(4, src.cols());
  //src_h.topRows(3) = src;
  //src_h.bottomRows(1) = Eigen::Matrix<double, 1, Eigen::Dynamic>::Ones(N);

  //// Apply an arbitrary SE(3) transformation
  //Eigen::Matrix4d T;
  //// clang-format off
  //T << 9.96926560e-01,  6.68735757e-02, -4.06664421e-02, -1.15576939e-01,
  //    -6.61289946e-02, 9.97617877e-01,  1.94008687e-02, -3.87705398e-02,
  //    4.18675510e-02, -1.66517807e-02,  9.98977765e-01, 1.14874890e-01,
  //    0,              0,                0,              1;
  //// clang-format on

  //// Apply transformation
  //Eigen::Matrix<double, 4, Eigen::Dynamic> tgt_h = T * src_h;
  //Eigen::Matrix<double, 3, Eigen::Dynamic> tgt = tgt_h.topRows(3);

  //// Add some noise & outliers
  //addNoiseAndOutliers(tgt);

  //// Convert to teaser point cloud
  //teaser::PointCloud tgt_cloud;
  //for (size_t i = 0; i < tgt.cols(); ++i) {
  //  tgt_cloud.push_back({static_cast<float>(tgt(0, i)), static_cast<float>(tgt(1, i)),
  //                       static_cast<float>(tgt(2, i))});
  //}
  std::string file_one ="D:/workspace/TEASER-plusplus-master/example/data/SS4B(A)_BOTTOM_B3_GLOC2_921_1_source.pcd";
  std::string file_two = "D:/workspace/TEASER-plusplus-master/example/data/SS4B(A)_BOTTOM_B3_GLOC2_921_1_template.pcd";
     // "../data/SS4B(A)_BOTTOM_B3_GLOC2_921_1_template.pcd";

  pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ>(file_one, *target_cloud) == -1) {
    PCL_ERROR("Couldn't read file 1.pcd \n");
    return (-1);
  }
  auto target = CloudPreprocessor(target_cloud, 0.01);

  // Loading second scan of room from new perspective.
  pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ>(file_two, *source_cloud) == -1) {
    PCL_ERROR("Couldn't read 2.pcd \n");
    return (-1);
  }

  auto source = CloudPreprocessor(source_cloud, 0.01);

   teaser::PointCloud src_cloud;
  for (int i = 0; i != source->points.size(); i++) {
    teaser::PointXYZ pt;
    pt.x = source->points[i].x;
    pt.y = source->points[i].y;
    pt.z = source->points[i].z;
    src_cloud.push_back(pt);
  }

  teaser::PointCloud tgt_cloud;
  for (int i = 0; i != target->points.size(); i++) {
    teaser::PointXYZ pt;
    pt.x = target->points[i].x;
    pt.y = target->points[i].y;
    pt.z = target->points[i].z;
    tgt_cloud.push_back(pt);
  }

  // Compute FPFH
  teaser::FPFHEstimation fpfh;
  auto obj_descriptors = fpfh.computeFPFHFeatures(src_cloud, 0.02, 0.04);
  auto scene_descriptors = fpfh.computeFPFHFeatures(tgt_cloud, 0.02, 0.04);

  teaser::Matcher matcher;
  auto correspondences = matcher.calculateCorrespondences(
      src_cloud, tgt_cloud, *obj_descriptors, *scene_descriptors, false, true, true, 0.95,2000);

  // Run TEASER++ registration
  // Prepare solver parameters
  teaser::RobustRegistrationSolver::Params params;
  params.noise_bound = NOISE_BOUND;
  params.cbar2 = 1;
  params.estimate_scaling = true;
  params.rotation_max_iterations = 120;
  params.rotation_gnc_factor = 1.4;
  params.rotation_estimation_algorithm =
      teaser::RobustRegistrationSolver::ROTATION_ESTIMATION_ALGORITHM::GNC_TLS;
  params.rotation_cost_threshold = 0.005;

  // Solve with TEASER++
  teaser::RobustRegistrationSolver solver(params);
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  solver.solve(src_cloud, tgt_cloud, correspondences);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  auto solution = solver.getSolution();

  solution.translation = solution.translation * 1000;

  Eigen::Matrix4d T; //±‰ªªæÿ’Û
  T.setIdentity();
  T.topLeftCorner(3, 3) << solution.rotation;
  T.topRightCorner(3, 1) << Eigen::Vector3d(solution.translation[0], solution.translation[1],
                                            solution.translation[2]);

  pcl::PointCloud<pcl::PointXYZ>::Ptr align_point_cloud(
      new pcl::PointCloud<pcl::PointXYZ>(source_cloud->width, source_cloud->height));
  pcl::transformPointCloud(*source_cloud, *align_point_cloud, T);

  pcl::io::savePCDFileBinary("./align_point_cloud.pcd", *align_point_cloud);
  // Compare results
  std::cout << "=====================================" << std::endl;
  std::cout << "          TEASER++ Results           " << std::endl;
  std::cout << "=====================================" << std::endl;
  /*std::cout << "Expected rotation: " << std::endl;
  std::cout << T.topLeftCorner(3, 3) << std::endl;*/
  std::cout << "Estimated rotation: " << std::endl;
  std::cout << solution.rotation << std::endl;
 /* std::cout << "Error (rad): " << getAngularError(T.topLeftCorner(3, 3), solution.rotation)
            << std::endl;*/
  std::cout << std::endl;
 /* std::cout << "Expected translation: " << std::endl;
  std::cout << T.topRightCorner(3, 1) << std::endl;*/
  std::cout << "Estimated translation: " << std::endl;
  std::cout << solution.translation << std::endl;
 /* std::cout << "Error (m): " << (T.topRightCorner(3, 1) - solution.translation).norm() << std::endl;*/
  std::cout << std::endl;
 /* std::cout << "Number of correspondences: " << N << std::endl;*/
  //std::cout << "Number of outliers: " << N_OUTLIERS << std::endl;
  std::cout << "Time taken (s): "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() /
                   1000000.0
            << std::endl;
}
