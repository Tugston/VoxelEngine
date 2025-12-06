/*
* File: EditorCamera.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-28 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "EditorCamera.h"

namespace Engine::Camera
{
	EditorCamera::EditorCamera() :
		m_Settings(), m_Location(glm::vec3(0.f, 0.f, 0.f)), m_ProjectionMatrix(), m_RightVector()
	{
		UpdateRotation(glm::vec3(0.f, 0.f, 0.f));
		UpdateVectors();
	}

	EditorCamera::EditorCamera(const glm::vec3& position) :
		m_Settings(), m_Location(position), m_ProjectionMatrix(), m_RightVector()
	{
		UpdateRotation(glm::vec3(0.f, 0.f, 0.f));
		UpdateVectors();
	}

	EditorCamera::EditorCamera(const glm::vec3& position, const glm::vec3& rotation, float speed) :
		m_Settings(speed), m_Location(position), m_EulerRotation(rotation)
	{
		UpdateRotation(m_EulerRotation);
		UpdateVectors();
	}

	void EditorCamera::UpdateVectors()
	{
		//rotation vector...
		//pitch, roll, yaw

		//forward vector recalculation
		glm::vec3 tempForward{};
		tempForward.x = cos(glm::radians(m_EulerRotation.y)) * cos(glm::radians(m_EulerRotation.x));
		tempForward.y = sin(glm::radians(m_EulerRotation.x));
		tempForward.z = sin(glm::radians(m_EulerRotation.y)) * cos(glm::radians(m_EulerRotation.x));
		m_ForwardVector = glm::normalize(tempForward);

		//update the new right and up vectors as well
		m_RightVector = CalculateRightVector();
		m_UpVector = CalculateUpVector();
	}

	void EditorCamera::UpdateRotation(const glm::vec3& newRotation)
	{
		//do quaternions later, euler is fine for now
		m_EulerRotation = newRotation;
	}

	glm::vec3 EditorCamera::CalculateUpVector() const
	{
		return glm::normalize(glm::cross(m_RightVector, m_ForwardVector));
	}

	glm::vec3 EditorCamera::CalculateRightVector() const
	{
		//positive y is up for this engine
		return glm::normalize(glm::cross(m_ForwardVector, glm::vec3(0.f, 1.f, 0.f)));
	}
}