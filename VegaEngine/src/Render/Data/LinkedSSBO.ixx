module;
#include "OpenGL.h"
export module Render:LinkedSSBO;
import :Buffer;
import std;

namespace Vega {

	template <typename CpuObject, typename GpuObject>
	concept Parsable = requires(CpuObject t) {
		{ t.Parse() } -> std::convertible_to<GpuObject>;
	};

	export template <typename CpuT, typename GpuT>
		requires Parsable<CpuT, GpuT>
	class LinkedSSBO
	{
	public:
		LinkedSSBO() {
			glGenBuffers(1, &_ID);
			_dataSet = false;
		}

		LinkedSSBO(const std::vector<CpuT>& data) {
			_nElements = data.size();
			_gpuObjects.resize(_nElements);
			for (size_t i = 0; i < _nElements; i++)
			{
				_gpuObjects[i] = data[i].Parse();
			}
			glGenBuffers(1, &_ID);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, _nElements * sizeof(GpuT), _gpuObjects.data(), GL_DYNAMIC_READ);
			_dataSet = true;
		}

		size_t GetReservedSize() const {
			return _nElements;
		}

		void SetData(const std::vector<CpuT>& data, size_t nElements = -1) {
			if (nElements == -1)
				_nElements = data.size();
			else
				_nElements = nElements;

			_gpuObjects.resize(_nElements);
			for (size_t i = 0; i < _nElements; i++)
			{
				_gpuObjects[i] = data[i].Parse();
			}
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, _nElements * sizeof(GpuT), _gpuObjects.data(), GL_DYNAMIC_READ);
			_dataSet = true;
		}

		void Bind(GLuint slot) const {
			if (!_dataSet) {
				Log.warn("Trying to bind SSBO whose data has not yet been set");
			}
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, _ID);
		}

		/// Updates a portion of the data on the GPU.
		/// Offset is in number of elements
		void UpdateData(const std::vector<CpuT>& data, size_t nSubElements = -1, size_t offset = 0) {
			if (nSubElements == -1)
				nSubElements = data.size();

			if (!_dataSet) {
				Log.error("Trying to update SSBO whose data has not yet been set");
				return;
			}
			if (_nElements < (offset + nSubElements)) {
				Log.error("Trying to update SSBO with subdata larget than allocated size");
				return;
			}

			for (size_t i = offset; i < offset + nSubElements; i++)
			{
				_gpuObjects[i] = data[i].Parse();
			}

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset * sizeof(GpuT), nSubElements * sizeof(GpuT), &_gpuObjects[offset]);
		}

		void Zero() {
			if (!_dataSet) {
				Log.error("Trying to zero SSBO whose data has not yet been set");
				return;
			}
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, _nElements * sizeof(GpuT), nullptr);
		}

		/// Gets data from the GPU.
		/// Offset is in number of elements
		void GetData(std::vector<GpuT>& data, size_t nSubElements = -1, size_t offset = 0) {
			if (nSubElements == -1)
				nSubElements = _nElements;

			if (!_dataSet) {
				Log.error("Trying to get data from SSBO whose data has not yet been set");
				return;
			}
			if (data.size() < nSubElements) {
				Log.error("Trying to get data from SSBO into array smaller than the data");
				return;
			}
			glGetNamedBufferSubData(_ID, offset * sizeof(GpuT), nSubElements * sizeof(GpuT), data.data());
		}

		void Reserve(size_t nElements) {
			_nElements = nElements;
			_gpuObjects.resize(_nElements);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, _nElements * sizeof(GpuT), nullptr, GL_DYNAMIC_READ);
			_dataSet = true;
		}

	private:
		GLuint _ID = 0;
		bool _dataSet = false;
		size_t _nElements = 0;

		std::vector<GpuT> _gpuObjects;
	};

}
