// C++ definition

#include "QCDNUM/QCDNUM.h"
#include "QCDNUM/QCDNUMfw.h"

#include <sstream>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define STR_EXPAND(top) #top
#define STR(tok) STR_EXPAND(tok)

namespace QCDNUM {

  /*
    ==========================================
    Subroutine and function calls in QCDNUM
    (corresponding to Table 2 of the write-up)
    ==========================================
  */
  
  /*--------------------------------------------------------------------
    Initialisation
  --------------------------------------------------------------------*/

  // Initialise
  void qcinit(int lun, string fname)
  {
    int ls = fname.size();
    std::vector<char> cfname(ls + 1);
    strcpy(&cfname[0],fname.c_str());
    fqcinitcpp(&lun,&cfname[0],&ls);
  }

  // Redirect output 
  void setlun(int lun, string fname)
  {
    int ls = fname.size();
    std::vector<char> cfname(ls + 1);
    strcpy(&cfname[0],fname.c_str());
    fsetluncpp(&lun,&cfname[0],&ls);
  }

  // Get next free lun
  int nxtlun(int lmin)
  {
    return fnxtlun(&lmin);
  }

  // Set parameters
  void setval(string opt, double val)
  {
    int ls = opt.size();
    std::vector<char> copt(ls + 1);
    strcpy(&copt[0],opt.c_str());
    fsetvalcpp(&copt[0],&ls,&val);
  }

  // Get parameters
  void getval(string opt, double &val)
  {
    int ls = opt.size();
    std::vector<char> copt(ls + 1);
    strcpy(&copt[0],opt.c_str());
    fgetvalcpp(&copt[0],&ls,&val);
  }
  
  // Set integer parameters
  void setint(string opt, int ival)
  {
    int ls = opt.size();
    std::vector<char> copt(ls + 1);
    strcpy(&copt[0],opt.c_str());
    fsetintcpp(&copt[0],&ls,&ival);
  }

  // Get integer parameters
  void getint(string opt, int &ival)
  {
    int ls = opt.size();
    std::vector<char> copt(ls + 1);
    strcpy(&copt[0],opt.c_str());
    fgetintcpp(&copt[0],&ls,&ival);
  }

  // Get|set qstore
  void qstore(string opt, int ival, double &val)
  {
    int ls = opt.size();
    std::vector<char> copt(ls + 1);
    strcpy(&copt[0],opt.c_str());
    fqstorecpp(&copt[0],&ls,&ival,&val);
  }
    
  /*--------------------------------------------------------------------
    Grid
  --------------------------------------------------------------------*/

  // Define x grid
  void gxmake(double *xmin, int *iwt, int n, int nxin, int &nxout, int iord)
  {
    fgxmake(xmin,iwt,&n,&nxin,&nxout,&iord);
  }

  // Get ix from x
  int ixfrmx(double x)
  {
    return fixfrmx(&x);
  }

  // Get x from ix
  double xfrmix(int ix)
  {
    return fxfrmix(&ix);
  }

  // Verify grid point
  int xxatix(double x, int ix)
  {
    return fxxatix(&x,&ix);
  }

  // Define muF2 grid
  void gqmake(double *qarr, double *wgt, int n, int nqin, int &nqout)
  {
    fgqmake(qarr,wgt,&n,&nqin,&nqout);
  }

  // Get imu from muF2
  int iqfrmq(double q2)
  {
    return fiqfrmq(&q2);
  }

  // Get muF2 from imu
  double qfrmiq(int iq)
  {
    return fqfrmiq(&iq);
  }

  // Verify grid point
  int qqatiq(double q2, int iq)
  {
    return fqqatiq(&q2,&iq);
  }

  // Get grid definition
  void grpars(int &nx, double &xmi, double &xma, int &nq, double &qmi, double &qma, int &iord)
  {
    fgrpars(&nx,&xmi,&xma,&nq,&qmi,&qma,&iord);
  }

  // Copy x grid
  void gxcopy(double *array, int n, int &nx)
  {
    fgxcopy(array,&n,&nx);
  }

  // Copy muF2 grid
  void gqcopy(double *array, int n, int &nq)
  {
    fgqcopy(array,&n,&nq);
  }

  /*--------------------------------------------------------------------
    Weights
  --------------------------------------------------------------------*/

  // Fill weight tables
  void fillwt(int itype, int &idmin, int &idmax, int &nwds)
  {
    ffillwt(&itype,&idmin,&idmax,&nwds);
  }

  // Dump weight tables
  void dmpwgt(int itype, int lun, string fname)
  {
    int ls = fname.size();
    std::vector<char> cfname(ls + 1);
    strcpy(&cfname[0],fname.c_str());
    fdmpwgtcpp(&itype,&lun,&cfname[0],&ls);
  }

  // Read weight tables
  void readwt(int lun, string fname, int &idmin, int &idmax, int &nwds, int &ierr)
  {
    int ls = fname.size();
    std::vector<char> cfname(ls + 1);
    strcpy(&cfname[0],fname.c_str());
    freadwtcpp(&lun,&cfname[0],&ls,&idmin,&idmax,&nwds,&ierr);
  }

  // Memory words used
  void nwused(int &nwtot, int &nwuse, int &ndummy)
  {
    fnwused(&nwtot,&nwuse,&ndummy);
  }

  /*--------------------------------------------------------------------
    Parameters
   -------------------------------------------------------------------*/

  // Set order
  void setord(int iord)
  {
    fsetord(&iord);
  }

  // Get order
  void getord(int &iord)
  {
    fgetord(&iord);
  }

  // Set alphas start value
  void setalf(double as0, double r20)
  {
    fsetalf(&as0,&r20);
  }

  // Get alphas start value
  void getalf(double &as0, double &r20)
  {
    fgetalf(&as0,&r20);
  }

  // Set nf or thresholds
  void setcbt(int nfix, int iqc, int iqb, int iqt)
  {
    fsetcbt(&nfix,&iqc,&iqb,&iqt);
  }

  // Set mfns parameters
  void mixfns(int nfix, double r2c, double r2b, double r2t)
  {
    fmixfns(&nfix,&r2c,&r2b,&r2t);
  }

  // Get nf or thresholds
  void getcbt(int &nfix, double &q2c, double &q2b, double &q2t)
  {
    fgetcbt(&nfix,&q2c,&q2b,&q2t);
  }

  // Get nf at imu
  int nflavs(int iq, int &ithresh)
  {
    return fnflavs(&iq,&ithresh);
  }

  // Set muF2 scale
  void setabr(double ar, double br)
  {
    fsetabr(&ar,&br);
  }

  // Get muF2 scale
  void getabr(double &ar, double &br)
  {
    fgetabr(&ar,&br);
  }

  // Convert muF2 to muR2
  double rfromf(double fscale2)
  {
    return frfromf(&fscale2);
  }

  // Convert muR2 to muF2
  double ffromr(double rscale2)
  {
    return fffromr(&rscale2);
  }

  // Set cuts
  void setcut(double xmi, double q2mi, double q2ma, double dummy)
  {
    fsetcut(&xmi,&q2mi,&q2ma,&dummy);
  }

  // Get cuts
  void getcut(double &xmi, double &q2mi, double &q2ma, double &dummy)
  {
    fgetcut(&xmi,&q2mi,&q2ma,&dummy);
  }

  // Copy parameter list
  void cpypar(double *array, int n, int iset)
  {
    fcpypar(array,&n,&iset);
  }

  // Get parameter key
  int keypar(int iset)
  {
    return fkeypar(&iset);
  }

  // Activate parameters
  void usepar(int iset)
  {
    fusepar(&iset);
  }

  // Push on a stack
  void pushcp()
  {
    fpushcp();
  }

  // Pull from a stack
  void pullcp()
  {
    fpullcp();
  }

  /*--------------------------------------------------------------------
    Evolution
  --------------------------------------------------------------------*/

  // Evolve alphas(muR2)
  double asfunc(double r2, int &nf, int &ierr)
  {
    return fasfunc(&r2,&nf,&ierr);
  }

  // Returns a_s^n(muF2)
  double altabn(int iset, int iq, int n, int &ierr)
  {
    return faltabn(&iset,&iq,&n,&ierr);
  }

  // Evolve PDFs
  void evolfg(int iset, double (*func) (int*, double*), double *def, int iq0, double &epsi)
  {
    fevolfg(&iset,func,def,&iq0,&epsi);
  }

  // Copy PDF set
  void pdfcpy(int iset1, int iset2)
  {
    fpdfcpy(&iset1,&iset2);
  }

  // Read external PDF set
  void extpdf(double (*func)(int*, double*, double*, bool*), int iset, int n, double offset, double &epsi)
  {
    fextpdf(func,&iset,&n,&offset,&epsi);
  }

  // Number of PDF tables
  int nptabs(int iset)
  {
    return fnptabs(&iset);
  }

  /*--------------------------------------------------------------------
    Interpolation
  --------------------------------------------------------------------*/

  // Get one basis PDF (xQ)
  double bvalxq(int iset, int id, double x, double qmu2, int ichk)
  {
    return fbvalxq(&iset,&id,&x,&qmu2,&ichk);
  }

  // Get one basis PDF (ij)
  double bvalij(int iset, int id, int ix, int iq, int ichk)
  {
    return fbvalij(&iset,&id,&ix,&iq,&ichk);
  }

  // Get one flavour PDF (xQ)
  double fvalxq(int iset, int id, double x, double qmu2, int ichk)
  {
    return ffvalxq(&iset,&id,&x,&qmu2,&ichk);
  }

  // Get one flavour PDF (ij)
  double fvalij(int iset, int id, int ix, int iq, int ichk)
  {
    return ffvalij(&iset,&id,&ix,&iq,&ichk);
  }

  // Get all flavours PDFs (xQ)
  void allfxq(int iset, double x, double qmu2, double *pdfs, int n, int ichk)
  {
    fallfxq(&iset,&x,&qmu2,pdfs,&n,&ichk);
  }

  // Get all flavours PDFs (ij)
  void allfij(int iset, int ix, int iq, double *pdfs, int n, int ichk)
  {
    fallfij(&iset,&ix,&iq,pdfs,&n,&ichk);
  }

  // Linear combination (xQ)
  double sumfxq(int iset, double *c, int isel, double x, double qmu2, int ichk)
  {
    return fsumfxq(&iset,c,&isel,&x,&qmu2,&ichk);
  }

  // Linear combination (ij)
  double sumfij(int iset, double *c, int isel, int ix, int iq, int ichk)
  {
    return fsumfij(&iset,c,&isel,&ix,&iq,&ichk);
  }


  // Check spline
  double splchk(int iset, int id, int iq)
  {
    return fsplchk(&iset,&id,&iq);
  }

  // Spline interpolation
  double fsplne(int iset, int id, double x, int iq)
  {
    return ffsplne(&iset,&id,&x,&iq);
  }

  // Make list PDFs
  void fflist(int iset, double *c, int m, double *x, double *q, double *f, int n, int ichk)
  {
    ffflist(&iset,c,&m,x,q,f,&n,&ichk);
  }

  // Make table of PDFs
  void ftable(int iset, double *c, int m, double *x, int nx, double *q, int nq, double *table, int ichk)
  {
    fftable(&iset,c,&m,x,&nx,q,&nq,table,&ichk);
  }

  /*--------------------------------------------------------------------
    Datacards
  --------------------------------------------------------------------*/

  // Process datacard file (???????????????)
  void qcards(void (*userkeys)(string*,int*,string*,int*,string*,int*,int*), string fname, int iprint)
  {
    int ls = fname.size();
    std::vector<char> cfname(ls + 1);
    strcpy(&cfname[0],fname.c_str());
    fqcardscpp(userkeys,&cfname[0],&ls,&iprint);
  }

  // Manage keycard
  void qcbook(string action, string key)
  {
    int l1 = action.size();
    std::vector<char> caction(l1 + 1);
    strcpy(&caction[0],action.c_str());
    int l2 = key.size();
    std::vector<char> ckey(l2 + 1);
    strcpy(&ckey[0],key.c_str());
    fqcbookcpp(&caction[0],&l1,&ckey[0],&l2);
  }

}
