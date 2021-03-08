#include "UniqueId.h"

#define UUID_SYSTEM_GENERATOR
#include "uuid.h"

using namespace uuids;

Rocket::UniqueId::UniqueId()
{
	m_uid = uuids::uuid_system_generator{}();
}
