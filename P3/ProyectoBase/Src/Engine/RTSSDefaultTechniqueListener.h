#pragma once

#include <OgreMaterialManager.h>

#include <string>


namespace Ogre
{
	class Technique;
	class Material;
	class Renderable;

	typedef std::string _StringBase;
	typedef _StringBase String;

	namespace RTShader
	{
		class ShaderGenerator;
	}
}

class RTSSDefaultTechniqueListener : public Ogre::MaterialManager::Listener
{
	private:
		Ogre::RTShader::ShaderGenerator* m_ShaderGenerator;			// The shader generator instance.	

	public:
		RTSSDefaultTechniqueListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator);
		~RTSSDefaultTechniqueListener();

		/** This is the hook point where shader based technique will be created.
		It will be called whenever the material manager won't find appropriate technique
		that satisfy the target scheme name. If the scheme name is out target RT Shader System
		scheme name we will try to create shader generated technique for it.
		*/
		virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
			const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex,
			const Ogre::Renderable* rend);
		
};

