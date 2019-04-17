#pragma once

#include "Resource/ResourceBundle.h"
#include "Design/IIterator.h"

namespace ivaldi {
	namespace res {
		using IResourceIterator = IIterator<ResourceBundle>;
		/*class IResourceIterator: public IIterator<ResourceBundle> {
		public:
			virtual ~IResourceIterator() = default;
		};*/
	}
}