#include "phaseLockedLoop.h"


void PLL(float alpha, pll_parameters *pll) {


		// SOGI part

		pll->yd = (alpha * numd0 + pll->xdz1 * numd1 + pll->xdz2 * numd2) - (pll->ydz1 * dend1 + pll->ydz2 * dend2);

		pll->ydz2 = pll->ydz1;
		pll->ydz1 = pll->yd;

		pll->xdz2 = pll->xdz1;
		pll->xdz1 = alpha;


		pll->yq = (alpha * numq0 + pll->xqz1 * numq1 + pll->xqz2 * numq2) - (pll->yqz1 * denq1 + pll->yqz2 * denq2);

		pll->yqz2 = pll->yqz1;
		pll->yqz1 = pll->yq;

		pll->xqz2 = pll->xqz1;
		pll->xqz1 = alpha;

		pll->q = pll->yd * cosf(pll->theta_unc) + pll->yq * sinf(pll->theta_unc);


		// sos-1

		pll->y1 = (pll->q * numy11 + pll->x1z1 * numy12 + pll->x1z2 * numy13) - (pll->y1z1 * deny12 + pll->y1z2 * deny13);

		pll->y1z2 = pll->y1z1;
		pll->y1z1 = pll->y1;

		pll->x1z2 = pll->x1z1;
		pll->x1z1 = pll->q;

		// sos-2

		pll->y2 = (pll->y1 * numy21 + pll->x2z1 * numy22 + pll->x2z2 * numy23) - (pll->y2z1 * deny22 + pll->y2z2 * deny23);

		pll->y2z2 = pll->y2z1;
		pll->y2z1 = pll->y2;

		pll->x2z2 = pll->x2z1;
		pll->x2z1 = pll->y1;


		// sos-3

		pll->y3 = (pll->y2 * numy31 + pll->x3z1 * numy32 + pll->x3z2 * numy33) - (pll->y3z1 * deny32 + pll->y3z2 * deny33);

		pll->y3z2 = pll->y3z1;
		pll->y3z1 = pll->y3;

		pll->x3z2 = pll->x3z1;
		pll->x3z1 = pll->y2;


		// loop 

		pll->out = 10*pll->y3+ pw;

		pll->theta_unc = pll->theta_unc + pll->out * pts;


		if (pll->theta_unc > 6.283185307179586f) {

			pll->theta_unc = 0;

		}

		pll->theta = pll->theta_unc; // hp filter applied  on inputs
		

		
		


}
