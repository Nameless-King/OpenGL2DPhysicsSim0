#pragma once

#include <vector>
#include "./ForceGenerator.h"
#include "./Object.h"

class ForceRegistry{
	protected:
		struct ForceRegistration{
			Object* obj;
			ForceGenerator* fg;
		};

		typedef std::vector<ForceRegistration> Registry;
		Registry m_registrations;

	public:
		void add(Object* obj, ForceGenerator* fg);
		void remove(Object* obj, ForceGenerator* fg);
		void clear();
		void updateForces(float dt);
};
