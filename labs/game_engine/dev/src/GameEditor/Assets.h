#pragma once
class Assets
{
public:
	typedef std::vector<boost::filesystem::path>		AssetList;

	Assets(void);
	virtual ~Assets(void);


private:
	AssetList											m_textures;
	AssetList											m_materials;
	AssetList											m_templates;
};
