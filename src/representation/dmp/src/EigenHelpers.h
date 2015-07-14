#include <Eigen/Core>

namespace dmp
{
using Eigen::ArrayXd;
using Eigen::MatrixXd;
using Eigen::ArrayXXd;

struct EigenHelpers
{

  static inline ArrayXd toEigen(std::vector<double> data){
    ArrayXd eig;
    eig.resize(data.size());
    for(unsigned int i=0; i<data.size(); i++)
      eig[i] = data[i];
    return eig;
  }

  static inline MatrixXd toEigen(std::vector<std::vector<double> > data){
    MatrixXd eig;
    if(data.size() == 0)
      eig.resize(0,0);
    else
      eig.resize(data.size(), data[0].size());
    for(unsigned int i=0; i<data.size(); i++){
      for(unsigned int j=0; j<data[i].size(); j++){
        eig(i,j) = data[i][j];
      }
    }
    return eig;
  }

  static inline std::vector<double> toStdVec(ArrayXd data){
    std::vector<double> vect(data.rows());
    for(unsigned int i=0; i<data.rows(); i++){
      vect[i] = data[i];
    }
    return vect;
  }

  static inline std::vector<std::vector<double> > toStdVec(MatrixXd data){
    std::vector<std::vector<double> >vect(data.rows());
    for(unsigned int i=0; i<data.rows(); i++){
      vect[i].resize(data.cols());
      for(unsigned int j=0; j<data.cols(); j++){
        vect[i][j] = data(i,j);
      }
    }
    return vect;
  }


  /**
   * Calculates the gradient function for \p in, e.g. the derivation.
   * The gradient is computed using central differences in the interior
   * and first differences at the boundaries.
   * The returned gradient hence has the same shape as the input array.
   *
   * \param dt distance between two points.
   *
   * @note this is the same as python's numpy.gradient()
   */
  static inline void gradient(const ArrayXXd& in, ArrayXXd& out, const double dt)
  {
    assert(in.cols() > 1);
    out.resize(in.rows(), in.cols());

    //forward difference quotient (special case for first element)
    out.col(0) = (in.col(1) - in.col(0)) / dt;

    const int end = in.cols() - 1;
    const double dt2 = 2*dt;
    for(int i = 1; i < end; ++i)
    {//central difference quotient for each inner element
      out.col(i) = (in.col(i+1) -in.col(i-1))/dt2;
    }
    //backward difference quotient (special case for last element)
    out.col(end) = (in.col(end) - in.col(end-1))/dt;
  }

};
}