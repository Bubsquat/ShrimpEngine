// manager for game cameras 
#ifndef _CameraManager
#define _CameraManager

#include "AzulCore.h"

class CameraManager
{
public:

	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator =(const CameraManager&) = delete;
	~CameraManager();


	void UpdateDefaultCam();
	void Update2DCamera();
	void SetCurrentCamera(Camera* newCamera);
	Camera* GetCurrentCamera();
	Camera* Get2DCamera();
	void SwitchToDefaultCamera();
	void UpdateCurrentCamera();


private:

	Camera* currentCamera;
	Camera* defaultCamera;
	Camera* ortho2DCamera;

	// default cam attributes

	struct CameraOrientation
	{
		Vect up3DCam;
		Vect pos3DCam;
		Vect lookAt3DCam;
	};

	CameraOrientation defaultCamStartPos;
	CameraOrientation defaultCamCurrentPos;

	float defaultCamSpeed;
	float defaultCamRotSpeed;
	

};




#endif _CameraManager
