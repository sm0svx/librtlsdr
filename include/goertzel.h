#ifndef __GOERTZEL_H
#define __GOERTZEL_H


struct goertzel
{
	float cosw;
	float sinw;
	float two_cosw;
	float q0;
	float q1;
};

static inline void goertzel_init(struct goertzel *g, float f, float samp_rate)
{
	float w = 2.0f * M_PI * (f / (float)samp_rate);
	g->cosw = cosf(w);
	g->sinw = sinf(w);
	g->two_cosw = 2.0f * g->cosw;
	g->q0 = g->q1 = 0.0f;
}

static inline void goertzel_reset(struct goertzel *g)
{
	g->q0 = g->q1 = 0.0f;
}

static inline void goertzel_calc(struct goertzel *g, float sample)
{
	float q2 = g->q1;
	g->q1 = g->q0;
	g->q0 = g->two_cosw * g->q1 - q2 + sample;
}

static inline float goertzel_mag_sqr(struct goertzel *g)
{
	return g->q0 * g->q0 + g->q1 * g->q1 - g->q0 * g->q1 * g->two_cosw;
}


#endif /* __GOERTZEL_H */
// vim: tabstop=8:softtabstop=8:shiftwidth=8:noexpandtab
