//THROWUP.C

#include "g_local.h"
#include "throwup.h"

//this makes you throw up
void ThrowUpNow(edict_t*self)
{
	vec3_t forward, right;
	vec3_t mouth_pos, spew_vector;
	float rnum;
	int i;

	//setting spew vector based on players view angles
	AngleVectors(self->client->v_angle, forward, right, NULL);

	//make the vomit originate from the players mouth
	VectorScale(forward, 24, mouth_pos);
	VectorAdd(mouth_pos, self->s.origin, mouth_pos);
	mouth_pos[2] += self->viewheight;

	//make the vomit come foward from the players mouth
	VectorScale(forward, 24, spew_vector);

	//blood opied from the spawn damage function
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_BLOOD);
	gi.WritePosition (mouth_pos);
	gi.WriteDir (spew_vector);
	gi.multicast(mouth_pos, MULTICAST_PVS);

	//randomly say somethin'
	rnum = random();
	if (rnum < 0.5)
		gi.bprintf(PRINT_MEDIUM, "Retch!\n");
	else if (rnum < 1000)
		gi.bprintf(PRINT_MEDIUM, "Bleeeeeeh!\n");
	else
		gi.bprintf(PRINT_MEDIUM, "WAT?!?!?!?\n");

	//randomly makes a sound
	/* rnum = random();
	if (rnum < 0.5)
		gi.sound(self, CHAN_BODY, SexedSoundIndex(self, "gurp1"), 1, ATTN_NORM, 0);
	else
		gi.sound(self, CHAN_BODY, SexedSoundIndex(self, "gurp2"), 1, ATTN_NORM, 0);
	*/
	gi.sound(self, CHAN_VOICE, gi.soundindex("misc/udeath.wav"), 1, ATTN_NORM, 0);

	// throw up gibs.
	for (i = 0; i<3; i++) {
		ThrowVomit (self, mouth_pos, forward, right, self->velocity);
	}

	// every now and again, cough up MEGA vomit
	if (random() < 0.1)
	{
		for (i = 0; i<10; i++) {
			ThrowVomit (self, mouth_pos, forward, right, self->velocity);
		}
	}
}