#include <iostream>
#include <omp.h>

#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/CXX11/Tensor>

#include <highfive/H5Easy.hpp> // для записи результатов рабты численной схемы
#include <toml.hpp> // для считывания файла конфигурации

int main() {
  std::ostream& log(std::cout);

  const auto config = toml::parse("./assets/config.toml");
  const auto tasks  = toml::find(config, "tasks");

  for(const auto& task : tasks.as_array()) {
      log << "Start processing task " << " : " << toml::find<std::string>(task, "name") << '\n';
      log<< "\t description: " << toml::find<std::string>(task, "descr") << '\n';

      const unsigned int xdim = toml::find<unsigned int >(task, "xdim");
      const unsigned int ydim = toml::find<unsigned int >(task, "ydim");
      const unsigned int zdim = toml::find<unsigned int >(task, "zdim");

      const double tfin = toml::find<double>(task, "tfin");

      double* u_cur_storage  = new double(xdim * ydim * zdim);
      double* u_prev_storage = new double(xdim * ydim * zdim);
      
      Eigen::TensorMap<Eigen::Tensor<double, 3>> U    (u_cur_storage, xdim, ydim, zdim);
      Eigen::TensorMap<Eigen::Tensor<double, 3>> Uprev(u_cur_storage, xdim, ydim, zdim);
      
      delete u_cur_storage; // [] ??
      delete u_prev_storage;
  }
  return 0;
}