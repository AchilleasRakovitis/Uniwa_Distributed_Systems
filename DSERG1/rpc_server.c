#include "askisi1.h"

float *
mo_1_svc(data *argp, struct svc_req *rqstp)
{
        printf("Mesos oros\n");

	static float result;

        int sum;

        //Algorithmos eyreshs mesoy oroy dianysmatos
        sum = 0;

        int i;
        
        for(i=0; i<argp->y.y_len; i++){
                sum += argp->y.y_val[i];     
        }

        result = (float)sum / (float)argp->y.y_len;
        printf("Mesos oros: %.2f\n", result);
        return &result;
}

apotelesma *
megel_1_svc(data *argp, struct svc_req *rqstp)
{
        printf("Megisto - Elaxisto\n");

        apotelesma *megel = malloc(sizeof(apotelesma));

        megel->minmax.minmax_len = 2;

        megel->minmax.minmax_val = malloc(2 * sizeof(int));


        //Kanoyme allocate ta ypoloipa stoixeia tis domis gia apofygh segmentation fault (den mas xreiazontai se ayto to procedure)
        megel->vec.vec_len = 2;
        megel->vec.vec_val = malloc(megel->vec.vec_len * sizeof(float));



        //Algoritmos eyreshs megistoy - elaxistoy 
        megel->minmax.minmax_val[0] = argp->y.y_val[0];

        megel->minmax.minmax_val[1] = argp->y.y_val[0];

        int i = 0;
        for(i=1; i<argp->y.y_len; i++){
                if (argp->y.y_val[i]>megel->minmax.minmax_val[0]){
                        megel->minmax.minmax_val[0] = argp->y.y_val[i];
                }
                if (argp->y.y_val[i]<megel->minmax.minmax_val[1]){
                        megel->minmax.minmax_val[1] = argp->y.y_val[i];
                }
        }
        
        
        printf("Megisto: %d\n", megel->minmax.minmax_val[0]);
        printf("Elaxisto: %d\n", megel->minmax.minmax_val[1]);


        return megel;
}

apotelesma *
ginom_1_svc(data *argp, struct svc_req *rqstp)
{	
        printf("Dianysma a*y\n");

        apotelesma *vector = malloc(sizeof(apotelesma));
        
        vector->vec.vec_len = argp->y.y_len;

        vector->vec.vec_val = malloc(vector->vec.vec_len * sizeof(float));


        //Kanoyme allocate ta ypoloipa stoixeia tis domis gia apofygh segmentation fault (den mas xreiazontai se ayto to procedure)
        vector->minmax.minmax_len = 2;
        vector->minmax.minmax_val = malloc(2 * sizeof(int)); 


        //Algorithmos eyreshs dianysmatos a*y
        int i;

        for(i = 0; i < vector->vec.vec_len; i++){
                vector->vec.vec_val[i] = argp->a * (float)argp->y.y_val[i];
                printf("%.2f\n", vector->vec.vec_val[i]);
        }

        return vector;
}