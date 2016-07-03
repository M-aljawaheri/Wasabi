#pragma once

#include "Wasabi.h"
#include "WBase.h"
#include "WMath.h"

struct WVertex {
	WVertex(void) {}
	WVertex(float x, float y, float z,
		float tx, float ty, float tz,
		float nx, float ny, float nz,
		float u, float v)
		: pos(x, y, z), tang(tx, ty, tz), norm(nx, ny, nz), texC(u, v) {
	};

	WVector3 pos;
	WVector3 tang;
	WVector3 norm;
	WVector2 texC;
};

class WGeometry : public WBase {
	virtual std::string GetTypeName() const;

	struct {
		VkBuffer buf;
		VkDeviceMemory mem;
	} m_vertices;

	struct {
		int count;
		VkBuffer buf;
		VkDeviceMemory mem;
	} m_indices;

	WVector3		m_maxPt;
	WVector3		m_minPt;

public:
	WGeometry(Wasabi* const app, unsigned int ID = 0);
	~WGeometry();

	WError				CreateCube(float fSize, bool bDynamic = false);

	WError				Draw();

	WVector3			GetMinPoint() const;
	WVector3			GetMaxPoint() const;

	virtual bool		Valid() const;
};

class WGeometryManager : public WManager<WGeometry> {
	friend class WGeometry;

	virtual std::string GetTypeName(void) const;

public:
	WGeometryManager(class Wasabi* const app);
};

