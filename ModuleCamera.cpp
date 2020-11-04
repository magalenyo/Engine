#include "ModuleCamera.h"
#include "Geometry/Frustum.h"
#include "GL/glew.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleTime.h"

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


	if (App->input->GetKey(SDL_SCANCODE_Q)) {
		App->camera->move(ModuleCamera::UP);
	}
	else if (App->input->GetKey(SDL_SCANCODE_E)) {
		App->camera->move(ModuleCamera::DOWN);
	}
	else if (App->input->GetKey(SDL_SCANCODE_W)) {
		App->camera->move(ModuleCamera::FORWARD);
	}
	else if (App->input->GetKey(SDL_SCANCODE_S)) {
		App->camera->move(ModuleCamera::BACKWARD);
	}
	else if (App->input->GetKey(SDL_SCANCODE_A)) {
		App->camera->move(ModuleCamera::LEFT);
	}
	else if (App->input->GetKey(SDL_SCANCODE_D)) {
		App->camera->move(ModuleCamera::RIGHT);
	}

	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
	return true;
}

void ModuleCamera::move(const CameraMovement& movementType)
{
	switch (movementType) {
		case UP:
			frustum.SetPos(float3(
				frustum.Pos().x, 
				frustum.Pos().y + (verticalSpeed * App->time->DeltaTime() * frustum.Up().Normalized().y), 
				frustum.Pos().z)
			);
			break;
		case DOWN:
			frustum.SetPos(float3(
				frustum.Pos().x,
				frustum.Pos().y - verticalSpeed * App->time->DeltaTime(),
				frustum.Pos().z)
			);
			break;
		case LEFT: {
			float3 newPosition = vec(frustum.Pos().x - (horizontalSpeed * App->time->DeltaTime() * frustum.WorldRight().x), frustum.Pos().y, frustum.Pos().z);
			frustum.SetPos(newPosition);
		}
			break;
		case RIGHT: {
			float3 newPosition = vec(frustum.Pos().x + (horizontalSpeed * App->time->DeltaTime() * frustum.WorldRight().x), frustum.Pos().y, frustum.Pos().z);
			frustum.SetPos(newPosition);
		}
			break;
		case FORWARD: {
			float3 newPosition = vec(frustum.Pos().x, frustum.Pos().y, (frustum.Pos().z + horizontalSpeed * App->time->DeltaTime()) * frustum.Front().z);
			frustum.SetPos(newPosition);
		}
			break;
		case BACKWARD: {
			float3 newPosition = vec(frustum.Pos().x, frustum.Pos().y, (frustum.Pos().z - horizontalSpeed * App->time->DeltaTime()) * frustum.Front().z);
			frustum.SetPos(newPosition);
		}
			break;
		default:
			break;
	}
}
