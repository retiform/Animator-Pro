/* truecolo.c - stuff to help me pretend that my pixels are RGB values
   and not an index into the color map.  */

#include "errcodes.h"
#include "jimk.h"
#include "inks.h"
#include "memory.h"
#include "palmenu.h"
#include "render.h"

/* Function: color_dif
 *
 *  Return the sum of the squares of the differences of the rgb
 *  components.
 */
int
color_dif(const Rgb3 *c1, const Rgb3 *c2)
{
	const int dr = c1->r - c2->r;
	const int dg = c1->g - c2->g;
	const int db = c1->b - c2->b;

	return dr*dr + dg*dg + db*db;
}

/* Function: closestc
 *
 *  Return the index of the closest match of an Rgb3 colour within an
 *  arbitrary-length table of Rgb3 colours.  A zero-length table is
 *  legit (FWIW), and results in a return value of 0.
 */
int
closestc(const Rgb3 *rgb, const Rgb3 *cmap, int count)
{
	unsigned int closest_diff2 = 620000;
	int closest_index = 0;
	int i;

	for (i = 0; i < count; i++) {
		const unsigned int diff2 = color_dif(rgb, cmap);

		if (diff2 < closest_diff2) {
			closest_diff2 = diff2;
			closest_index = i;

			if (diff2 == 0)
				break;
		}

		cmap++;
	}

	return closest_index;
}

/* Function: true_blend
 *
 *  This routine blends the c1 and c2 colours based on the percent,
 *  yielding a new colour in d.
 */
void true_blend(Rgb3 *c1,Rgb3 *c2,UBYTE percent,Rgb3 *d)
{
	UBYTE vpercent;

	vpercent = 100-percent;
	d->r = (c1->r * vpercent + c2->r * percent + 50)/100;
	d->g = (c1->g * vpercent + c2->g * percent + 50)/100;
	d->b = (c1->b * vpercent + c2->b * percent + 50)/100;
}

#ifdef SLUFFED
void true_fades(UBYTE *c1,UBYTE *rgb,int p,int q,UBYTE *d,int count)
{
int vp;
int q2;

	vp = q - p;
	q2 = q/2;
	while (--count >= 0)
	{
		*d++ = (*c1++ * vp + rgb[0] * p + q2)/q;
		*d++ = (*c1++ * vp + rgb[1] * p + q2)/q;
		*d++ = (*c1++ * vp + rgb[2] * p + q2)/q;
	}
}
#endif /* SLUFFED */


static int shuffle_cmap(Cmap *s1cmap,Cmap *s2cmap,Cmap *dcmap)
{
int i;
int dsize;
Rgb3 *p;
Rgb3 *d;
Rgb3 *s1;
Rgb3 *s2;


	p = d = dcmap->ctab;
	s1 = s1cmap->ctab;
	s2 = s2cmap->ctab;

	dsize = 0;
	i = COLORS;
	while (--i >= 0)
	{
		if (!in_ctable(s1, d, dsize) )
		{
			pj_copy_bytes(s1, p, 3);
			++p;
			dsize++;
		}
		++s1;
	}
	i = COLORS;
	while (--i >= 0)
	{
		if (!in_ctable(s2, d, dsize) )
		{
			*p = *s2;
			++p;
			dsize++;
		}
		++s2;
	}
	return(dsize);
}

int compromise_cmap(Cmap *s1,Cmap *s2,Cmap *d)
{
Cmap *ccmap;
long ccount;

	if(pj_cmap_alloc(&ccmap,2*COLORS) < Success)
		return(0);
	pj_cmap_copy(s1,ccmap);  /* just in case... */
	ccount = shuffle_cmap(s1,s2,ccmap);
	pack_ctable(ccmap->ctab,ccount,d->ctab,COLORS);
	if(ccount < COLORS)
		fold_in_mucolors(d,ccount,vb.screen);
	pj_cmap_free(ccmap);
	return(1);
}
