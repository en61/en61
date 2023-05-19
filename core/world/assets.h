#pragma once

#include <core/common.h>

#include <core/renderer/shader.h>
#include <core/renderer/model.h>

namespace en61 {

class AssetManager {
public:
	AssetManager(const std::string &path);

	void SetDir(const std::string &dir) { _dir = dir; }
	std::string GetDir() const { return _dir; }


	template <class _Type>
	Ref<_Type> Load(const std::string &path) {
		WrongAssetType(typeid(_Type));
		return {};
	}

	template <class _Type>
	Ref<_Type> Load(const std::string &path1, const std::string &path2) {
		WrongAssetType(typeid(_Type));
		return {};
	}

protected:
	void WrongAssetType(const std::type_info &info);

protected:
	std::string _dir;
};

// thin wrapper over Ref to asset
template <class _Type>
class Asset {
public:
	Asset(AssetManager &manager, const std::string &path) {
		_value = manager.Load<_Type>(path);
	}

	Asset(AssetManager &manager, const std::string &path1, const std::string &path2) {
		_value = manager.Load<_Type>(path1, path2);
	}

	operator Ref<_Type>() {
		return _value;
	}

	Ref<_Type> GetValue() const { return _value; }
	void SetValue(Ref<_Type> nv) { _value = nv; }

protected:
	Ref<_Type> _value;
};


} // namespace en61
