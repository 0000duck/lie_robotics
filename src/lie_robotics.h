

    
#pragma once
#include <iostream>

#include <Eigen/Dense>
#include <vector>
#define JOINTNUM 6
namespace lr {
    typedef Eigen::Matrix<double, JOINTNUM, 1> JVec;
    typedef Eigen::Matrix<double, 4, 4> SE3;
    typedef Eigen::Matrix<double, 3, 3> SO3;
    typedef Eigen::Matrix<double, 4, 4> se3;
    typedef Eigen::Matrix<double, 3, 3> so3;
    typedef Eigen::Matrix<double, 6, JOINTNUM> ScrewList;
    typedef Eigen::Matrix<double, 6, JOINTNUM> Jacobian;
    typedef Eigen::Matrix<double, JOINTNUM,6 > pinvJacobian;
    typedef Eigen::Matrix<double, 6*JOINTNUM, JOINTNUM> DerivativeJacobianVec;
    typedef Eigen::Matrix<double, 6*JOINTNUM, 1> vecJVec;
    typedef Eigen::Matrix<double, 6, 1> Vector6d;   
    typedef Eigen::Matrix<double, 3, 1> Vector3d;   
    typedef Eigen::Matrix<double, 4, 1> Vector4d;  
    typedef Eigen::Matrix<double, 6, 6> Matrix6d;  
    typedef Eigen::Matrix<double, 3, 3> Matrix3d;  
    typedef Eigen::Matrix<double, 6, JOINTNUM> Matrix6xn;
    typedef Eigen::Matrix<double, 6, JOINTNUM+1> Matrix6xn_1;
    typedef Eigen::Matrix<double, JOINTNUM, JOINTNUM> MassMat;
    Matrix6d ad(const Vector6d& V) ;
    Matrix6d Ad(const SE3& T);
	Matrix6d AdInv(const SE3& T);    
    SE3 TransInv(const SE3& T) ;
    SO3 TransToR(const SE3& T);
    Vector3d TransToP(const SE3& T);
    Vector6d se3ToVec(const se3& T);
    Vector3d so3ToVec(const so3& so3mat);
    so3 VecToso3(const Vector3d& omg);
    se3 VecTose3(const Vector6d& V);
    bool NearZero(const double val) ;
    SO3 MatrixExp3(const so3& so3mat);
    SE3 MatrixExp6(const se3& se3mat);
    so3 MatrixLog3(const SO3& R);
    se3 MatrixLog6(const SE3& T);
    SE3 FKinSpace(const SE3& M, const ScrewList& Slist, const JVec& thetaList);
    SE3 FKinBody(const SE3& M, const ScrewList& Blist, const JVec& thetaList);
    Jacobian JacobianSpace(const ScrewList& Slist, const JVec& thetaList);
    Jacobian JacobianBody(const ScrewList& Blist, const JVec& thetaList) ;
    SE3 RpToTrans(const Matrix3d& R, const Vector3d& p);
    bool IKinBody(const ScrewList& Blist, const SE3& M, const SE3& T,
		JVec& thetalist, double eomg, double ev);
    bool IKinSpace(const ScrewList& Slist, const SE3& M, const SE3& T,
		JVec& thetalist, double eomg, double ev) ;
    JVec InverseDynamics(const JVec& thetalist, const JVec& dthetalist, const JVec& ddthetalist,
                  const Vector3d& g, const Vector6d& Ftip, const std::vector<SE3>& Mlist,
                  const std::vector<Matrix6d>& Glist, const ScrewList& Slist);
    JVec GravityForces(const JVec& thetalist, const Vector3d& g,
                  const std::vector<SE3>& Mlist, const std::vector<Matrix6d>& Glist, const ScrewList& Slist) ;                                    
    MassMat MassMatrix(const JVec& thetalist, const std::vector<SE3>& Mlist, const std::vector<Matrix6d>& Glist, const ScrewList& Slist) ;                                    
    JVec VelQuadraticForces(const JVec& thetalist, const JVec& dthetalist,const std::vector<SE3>& Mlist, const std::vector<Matrix6d>& Glist, const ScrewList& Slist) ;
    JVec EndEffectorForces(const JVec& thetalist, const Vector6d& Ftip,const std::vector<SE3>& Mlist, const std::vector<Matrix6d>& Glist, const ScrewList& Slist);
    JVec ForwardDynamics(const JVec& thetalist, const JVec& dthetalist, const JVec& taulist,
                  const Vector3d& g, const Vector6d& Ftip, const std::vector<SE3>& Mlist,
                  const std::vector<Matrix6d>& Glist, const ScrewList& Slist);                      
    void EulerStep(JVec& thetalist, JVec& dthetalist, const JVec& ddthetalist, double dt);                                    
    Vector3d QuinticTimeScalingKinematics(double s0,double sT,double ds0,double dsT,double dds0,double ddsT,double Tf, double t) ;
    void FKinBody(const SE3& M,const ScrewList& Blist, const JVec& q ,const JVec& dq, SE3 &T, Jacobian &Jb,Jacobian& dJb);
    Matrix3d dexp3(const Vector3d& xi);
    Matrix3d dlog3(const Vector3d& xi);
    Matrix6d dexp6(const Vector6d& lambda);
    Matrix3d ddexp3(const Vector3d& xi, const Vector3d& dxi);
    Matrix3d dddexp3(const Vector3d& xi, const Vector3d& dxi, const Vector3d& y, const Vector3d& dy);
    Matrix6d ddexp6(const Vector6d& lambda, const Vector6d& lambda_dot);
    Matrix3d skew_sum(const Vector3d& a, const Vector3d& b);
    Matrix3d ddlog3(const Vector3d& xi, const Vector3d& dxi);
    Matrix3d dddlog3(const Vector3d& xi, const Vector3d& dxi, const Vector3d& y, const Vector3d& dy);
    Matrix6d dlog6(const Vector6d& lambda);
    Matrix6d ddlog6(const Vector6d& lambda, const Vector6d& lambda_dot) ;    
    void LieScrewTrajectory(const SE3 X0,const SE3 XT,const Vector6d V0,const Vector6d VT,const Vector6d dV0,const Vector6d dVT,double Tf,int N,std::vector<SE3>&Xd_list,std::vector<Vector6d>&Vd_list,std::vector<Vector6d>&dVd_list);
}


