#include "ModuleCamera.h"
#include "Geometry/Frustum.h"
#include "GL/glew.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleTime.h"
#include "Math/float3x3.h"


ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);

	frustum.SetPos(float3(0, 1, -2));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);

	return true;
}

update_status ModuleCamera::Update()
{
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);		// to set white lines

	//frustum;
	float4x4 projectionGL = frustum.ProjectionMatrix().Transposed(); //<-- Important to transpose!
	float4x4 viewMatrix = frustum.ViewMatrix();

	//Send the frustum view matrix to OpenGL

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*viewMatrix.Transposed().v);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*projectionGL.v);


	glLineWidth(1.0f);
	float d = 200.0f;			// grid w
	glBegin(GL_LINES);			// grid creation
	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}
	glEnd();

	glLineWidth(2.0f);
	glBegin(GL_LINES);			// this is to start writting lines
	// red X
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);
	// green Y
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

	// blue Z
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);
	glEnd();				// this is to end writing lines
	glLineWidth(1.0f);

	// SEND THE PROJECTIONMATRIX AND VIEWMATRIX

	/* SPEED CONTROL */
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) && App->input->GetKey(SDL_SCANCODE_LSHIFT) != KEY_REPEAT) {
		increaseSpeed();
	}
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_UP) {
		resetSpeed();
	}
	/* SPEED CONTROL */

	if (App->input->GetKey(SDL_SCANCODE_Q)) {
		App->camera->move(CameraMovement::UP);
	}
	if (App->input->GetKey(SDL_SCANCODE_E)) {
		App->camera->move(CameraMovement::DOWN);
	}
	if (App->input->GetKey(SDL_SCANCODE_W) || App->input->GetMouseWheelState() == ModuleInput::MouseWheelState::SCROLLING_UP) {
		App->camera->move(CameraMovement::FORWARD);
	}
	if (App->input->GetKey(SDL_SCANCODE_S) || App->input->GetMouseWheelState() == ModuleInput::MouseWheelState::SCROLLING_DOWN) {
		App->camera->move(CameraMovement::BACKWARD);
	}
	if (App->input->GetKey(SDL_SCANCODE_A)) {
		App->camera->move(CameraMovement::LEFT);
	}
	if (App->input->GetKey(SDL_SCANCODE_D)) {
		App->camera->move(CameraMovement::RIGHT);
	}
	if (App->input->GetKey(SDL_SCANCODE_UP)) {
		App->camera->rotate(CameraRotation::PITCH_POSITIVE);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
		App->camera->rotate(CameraRotation::PITCH_NEGATIVE);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT)) {
		App->camera->rotate(CameraRotation::YAW_NEGATIVE);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT)) {
		App->camera->rotate(CameraRotation::YAW_POSITIVE);
	}
	
	#ifdef _DEBUG	
	//LOG(frustum.ToString().c_str());
	float3 rotDegree = frustum.ViewMatrix().ToEulerXYZ();
	rotDegree = float3(rotDegree.x * RADTODEG, rotDegree.y * RADTODEG, rotDegree.z * RADTODEG);
	LOG(rotDegree.ToString().c_str());
	#endif // _DEBUG

	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
	return true;
}

void ModuleCamera::move(const CameraMovement& movementType)
{
	switch (movementType) {
		case UP: {
			float3 newPosition = frustum.Up().Normalized() * verticalSpeed * App->time->DeltaTime();
			frustum.SetPos(frustum.Pos() + newPosition);
		}
			break;
		case DOWN: {
			float3 newPosition = frustum.Up().Normalized() * verticalSpeed * App->time->DeltaTime();
			frustum.SetPos(frustum.Pos() - newPosition);
		}

			break;
		case LEFT: {
			float3 newPosition = frustum.WorldRight().Normalized() * horizontalSpeed * App->time->DeltaTime();
			frustum.SetPos(frustum.Pos() - newPosition);
		}
			break;
		case RIGHT: {
			float3 newPosition = frustum.WorldRight().Normalized() * horizontalSpeed * App->time->DeltaTime();
			frustum.SetPos(frustum.Pos() + newPosition);
		}
			break;
		case FORWARD: {
			float mouseSpeedMultiplier = App->input->GetMouseWheelState() == ModuleInput::MouseWheelState::SCROLLING_UP ? 4 : 1;
			float3 newPosition = frustum.Front().Normalized() * horizontalSpeed * mouseSpeedMultiplier * App->time->DeltaTime();
			frustum.SetPos(frustum.Pos() + newPosition);
		}
			break;
		case BACKWARD: {
			float mouseSpeedMultiplier = App->input->GetMouseWheelState() == ModuleInput::MouseWheelState::SCROLLING_DOWN ? 4 : 1;
			float3 newPosition = frustum.Front().Normalized() * horizontalSpeed * mouseSpeedMultiplier * App->time->DeltaTime();
			frustum.SetPos(frustum.Pos() - newPosition);
		}
			break;
		default:
			break;

	}
}

void ModuleCamera::rotate(const CameraRotation& rotationType)
{
	switch (rotationType) {
		case PITCH_POSITIVE: {
			//float3x3 rotation = float3x3::RotateY(-rotationSpeed * DEGTORAD * App->time->DeltaTime());
			// i think this is the absolute
			float3x3 rotation = float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), rotationSpeed * DEGTORAD * App->time->DeltaTime());
			frustum.SetFront(rotation * frustum.Front().Normalized());
			frustum.SetUp(rotation * frustum.Up().Normalized());
		}
			break;
		case PITCH_NEGATIVE: {
			float3x3 rotation = float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), -rotationSpeed * DEGTORAD * App->time->DeltaTime());
			frustum.SetFront(rotation * frustum.Front().Normalized());
			frustum.SetUp(rotation * frustum.Up().Normalized());
		}
		   break;
		case YAW_POSITIVE: {
			float3x3 rotation = float3x3::RotateY(-rotationSpeed * DEGTORAD * App->time->DeltaTime());	// this makes it absolute
			//float3x3 rotation = float3x3::RotateAxisAngle(frustum.Up().Normalized(), -rotationSpeed * DEGTORAD * App->time->DeltaTime());			// this makes it relative
			frustum.SetFront(rotation * frustum.Front().Normalized());
			frustum.SetUp(rotation * frustum.Up().Normalized());
		}
			break;
		case YAW_NEGATIVE: {
			float3x3 rotation = float3x3::RotateY(rotationSpeed * DEGTORAD * App->time->DeltaTime());
			//float3x3 rotation = float3x3::RotateAxisAngle(frustum.Up().Normalized(), rotationSpeed * DEGTORAD * App->time->DeltaTime());
			frustum.SetFront(rotation * frustum.Front().Normalized());
			frustum.SetUp(rotation * frustum.Up().Normalized());
			
				
		}
			break;
	}
}

void ModuleCamera::resetSpeed()
{
	verticalSpeed = 1.0f;
	horizontalSpeed = 1.0f;
	rotationSpeed = 10.0f;
}

void ModuleCamera::increaseSpeed()
{
	verticalSpeed *= 2.0f;
	horizontalSpeed *= 2.0f;
	rotationSpeed *= 2.0f;
}
