

struct ws10dofhandle
{
	/*acceleration in m/s/s
	 *not adjusted for constant gravity
	 */
	float Accx;
	float Accy;
	float Accz;
	
	/*degrees /s/s ???
	 *
	 */
	float Gyrox;
	float Gyroy;
	float Gyroz;
	
	/*degrees from xxxx ??
	 *
	 */
	float Compx;
	float Compy;
	float Compz;
	
	float pressure;
};
typedef struct ws10dofhandle ws10dofhandle;//make better short type name 
