#include <noether_tpp/mesh_modifiers/subset_extraction/vtk_cutter_extractor.h>

#include <pcl/io/vtk_lib_io.h>
#include <vtkAbstractCellLocator.h>
#include <vtkSelectPolyData.h>
#include <vtkSphereSource.h>

namespace noether
{
void test()
{
  vtkNew<vtkSphereSource> sphereSource;
  sphereSource->SetPhiResolution(50);
  sphereSource->SetThetaResolution(100);
  sphereSource->Update();

  vtkNew<vtkPoints> selectionPoints;

  selectionPoints->InsertPoint(0, -0.16553, 0.135971, 0.451972);
  selectionPoints->InsertPoint(1, -0.0880123, -0.134952, 0.4747);
  selectionPoints->InsertPoint(2, 0.00292618, -0.134604, 0.482459);
  selectionPoints->InsertPoint(3, 0.0641941, 0.067112, 0.490947);
  selectionPoints->InsertPoint(4, 0.15577, 0.0734765, 0.469245);
  selectionPoints->InsertPoint(5, 0.166667, -0.129217, 0.454622);
  selectionPoints->InsertPoint(6, 0.241259, -0.123363, 0.420581);
  selectionPoints->InsertPoint(7, 0.240334, 0.0727106, 0.432555);
  selectionPoints->InsertPoint(8, 0.308529, 0.0844311, 0.384357);
  selectionPoints->InsertPoint(9, 0.32672, -0.121674, 0.359187);
  selectionPoints->InsertPoint(10, 0.380721, -0.117342, 0.302527);
  selectionPoints->InsertPoint(11, 0.387804, 0.0455074, 0.312375);
  selectionPoints->InsertPoint(12, 0.43943, -0.111673, 0.211707);
  selectionPoints->InsertPoint(13, 0.470984, -0.0801913, 0.147919);
  selectionPoints->InsertPoint(14, 0.436777, 0.0688872, 0.233021);
  selectionPoints->InsertPoint(15, 0.44874, 0.188852, 0.109882);
  selectionPoints->InsertPoint(16, 0.391352, 0.254285, 0.176943);
  selectionPoints->InsertPoint(17, 0.373274, 0.154162, 0.294296);
  selectionPoints->InsertPoint(18, 0.274659, 0.311654, 0.276609);
  selectionPoints->InsertPoint(19, 0.206068, 0.31396, 0.329702);
  selectionPoints->InsertPoint(20, 0.263789, 0.174982, 0.387308);
  selectionPoints->InsertPoint(21, 0.213034, 0.175485, 0.417142);
  selectionPoints->InsertPoint(22, 0.169113, 0.261974, 0.390286);
  selectionPoints->InsertPoint(23, 0.102552, 0.25997, 0.414814);
  selectionPoints->InsertPoint(24, 0.131512, 0.161254, 0.454705);
  selectionPoints->InsertPoint(25, 0.000192443, 0.156264, 0.475307);
  selectionPoints->InsertPoint(26, -0.0392091, 0.000251724, 0.499943);
  selectionPoints->InsertPoint(27, -0.096161, 0.159646, 0.46438);

  vtkNew<vtkSelectPolyData> loop;
  loop->SetInputConnection(sphereSource->GetOutputPort());
  loop->SetLoop(selectionPoints);
  // loop->GenerateSelectionScalarsOn();
  loop->SetSelectionModeToSmallestRegion(); // negative scalars inside
  loop->Update();

  vtkSmartPointer<vtkPolyData> poly = loop->GetOutput();
  auto n_points = poly->GetNumberOfPoints();
  auto n_polys = poly->GetNumberOfPolys();
  n_points + n_polys;
}

pcl::PolygonMesh VtkCutterExtractor::extract(const pcl::PolygonMesh& mesh, const Eigen::MatrixX3d& boundary) const
{
  test();

  auto mesh_poly = vtkSmartPointer<vtkPolyData>::New();
  pcl::io::mesh2vtk(mesh, mesh_poly);

  vtkNew<vtkPoints> loop;
  for (Eigen::Index i = 0; i < boundary.rows(); ++i)
    loop->InsertPoint(static_cast<vtkIdType>(i), boundary.row(i).data());

  vtkNew<vtkSelectPolyData> selector;
  selector->SetInputData(mesh_poly);
  selector->SetLoop(loop);

  Eigen::Vector3d mean = boundary.colwise().mean();
  // selector->SetSelectionModeToSmallestRegion();
  selector->SetSelectionModeToClosestPointRegion();
  selector->SetClosestPoint(mean.data());
  selector->Update();

  //
  vtkSmartPointer<vtkPolyData> output_poly = selector->GetOutput();

  pcl::PolygonMesh output;
  pcl::io::vtk2mesh(output_poly, output);

  return output;
}

} // namespace noether
