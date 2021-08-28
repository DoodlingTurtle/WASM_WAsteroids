#pragma once

namespace RGNDS::World {

	class Updateable {
	public:
		virtual void onUpdate(float deltaTime) = 0;
	};

};


