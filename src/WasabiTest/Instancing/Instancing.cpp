#include "Instancing/Instancing.hpp"

InstancingDemo::InstancingDemo(Wasabi* const app) : WTestState(app) {
	character = nullptr;
	geometry = nullptr;
	texture = nullptr;
}

void InstancingDemo::Load() {
	WFile file(m_app);
	CheckError(file.Open("media/dante.WSBI"));
	assert(file.GetAssetsCount() >= 1);
	CheckError(file.LoadAsset<WGeometry>("dante-geometry", &geometry, WGeometry::LoadArgs()));
	file.Close();

	texture = new WImage(m_app);
	CheckError(texture->Load("media/dante.png"));

	character = m_app->ObjectManager->CreateObject();
	character->SetGeometry(geometry);
	character->GetMaterials().SetTexture("diffuseTexture", texture);

	int instancing = 2;

	if (instancing) {
		int nx = 20, nz = 80;
		float width = 3.0f * nx, depth = (float)nz;
		((WasabiTester*)m_app)->SetZoom(-depth * 1.2f);
		if (instancing == 2)
			character->InitInstancing(nx * nz);
		for (int x = 0; x < nx; x++) {
			for (int z = 0; z < nz; z++) {
				float px = (((float)x / (float)(nx - 1)) - 0.5f) * width;
				float pz = (((float)z / (float)(nz - 1)) - 0.5f) * depth;
				WInstance* inst = character->CreateInstance();
				if (inst) {
					inst->SetPosition(px, 0, pz);
				}

				if (instancing == 1) {
					WObject* c = m_app->ObjectManager->CreateObject();
					c->SetGeometry(geometry);
					c->GetMaterials().SetTexture("diffuseTexture", texture);
					c->SetPosition(px, 0, pz);
					objectsV.push_back(c);
				}
			}
		}
	}
}

void InstancingDemo::Update(float fDeltaTime) {
	UNREFERENCED_PARAMETER(fDeltaTime);
}

void InstancingDemo::Cleanup() {
	W_SAFE_REMOVEREF(character);
	W_SAFE_REMOVEREF(geometry);
	W_SAFE_REMOVEREF(texture);
	for (uint32_t i = 0; i < objectsV.size(); i++)
		objectsV[i]->RemoveReference();
	objectsV.clear();
}
