#ifndef DNA_FRACTURE_TYPES_H
#define DNA_FRACTURE_TYPES_H

#include "DNA_mesh_types.h"
#include "DNA_object_types.h"
#include "BLI_utildefines.h"

#ifdef __cplusplus
extern "C" {
#endif

struct DerivedMesh;

typedef struct PointCloud {
	float **points;	// just a bunch of positions in space
	int totpoints; // number of positions
	char pad[4];
} PointCloud;
				
typedef struct Shard {
	struct BMVert **vertices;
	struct BMEdge **edges;
	struct BMFace **faces; //need all geometry quickly possibly, for cutting tool, stanztools, for all, because there are no intermediate objects... 
	struct BoundBox *bb; // might be useful for collision tests
	float *vertco;		// hmm this was necessary for simulation itself, storing the restposition of the verts
	float centroid[3];	// centroid of shard, calculated during fracture
	float start_co[3];	// hmm this was necessary for simulation itself, storing the restposition of the centroid
	int *neighbor_ids;	// neighbors of me... might be necessary for easier compounding or fracture, dont need to iterate over all.... searchradius ?
	int shard_id;	// the identifier
	int vertex_count; // number of verts in this shard, need counts for edge face too
	int edge_count;
	int face_count;
	int neighbor_count; // counts of neighbor islands
	char pad[4];
} Shard;

typedef struct FracMesh {
	struct BMesh *fractured_mesh; //the entire fractured mesh state, 
	Shard **shard_map;	//groups of mesh elements to islands, hmm generated by fracture itself
	int shard_count;	//how many islands we have
	char pad[4];
} FracMesh;

typedef struct FracHistory {
	FracMesh **frac_states; // "indexed" by frames ? handle this in iterator...?
	int *frame_map; // only step in iterator when past or before according frame... important for replaying from cache
					// need a framemap; to trigger step changes by frame since we dont have neither user interaction nor feedback from the sim
					// this must be part of the history and could be in pointcache as well
	int state_count;
	char pad[4];
} FracHistory;

#ifdef __cplusplus
}
#endif

#endif // DNA_FRACTURE_TYPES_H
