module;
#include "OpenGL.h"
export module Render:Buffer;
import Utility;
import std;

export namespace Vega {

	template <typename T>
	class SSBO
	{
	public:
		SSBO() {
			glGenBuffers(1, &_ID);
			_dataSet = false;
		}

		SSBO(const std::vector<T>& data) {
			glGenBuffers(1, &_ID);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(T), data.data(), GL_DYNAMIC_READ);
			_dataSet = true;
			_nElements = data.size();
		}

		size_t GetReservedSize() const {
			return _nElements;
		}

		void SetData(const std::vector<T>& data, size_t nElements = -1) {
			if (nElements == -1)
				_nElements = data.size();
			else
				_nElements = nElements;

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T) * _nElements, data.data(), GL_DYNAMIC_READ);
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
		void UpdateData(const std::vector<T>& data, size_t nSubElements = -1, size_t offset = 0) {
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
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset * sizeof(T), nSubElements * sizeof(T), &data[offset]);
		}

		void Zero() {
			if (!_dataSet) {
				Log.error("Trying to zero SSBO whose data has not yet been set");
				return;
			}
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, _nElements * sizeof(T), nullptr);
		}

		/// Gets data from the GPU.
		/// Offset is in number of elements
		void GetData(std::vector<T>& data, size_t nSubElements = -1, size_t offset = 0) {
			if (nSubElements == -1) {
				nSubElements = _nElements;
			}
			if (!_dataSet) {
				Log.error("Trying to get data from SSBO whose data has not yet been set");
				return;
			}
			if (sizeof(data) < nSubElements * sizeof(T)) {
				Log.error("Trying to get data from SSBO into array smaller than the data");
				return;
			}
			glGetNamedBufferSubData(_ID, offset * sizeof(T), nSubElements * sizeof(T), &data);
		}

		void Reserve(size_t nElements) {
			_nElements = nElements;
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, _nElements * sizeof(T), nullptr, GL_DYNAMIC_READ);
			_dataSet = true;
		}

	private:
		GLuint _ID = 0;
		bool _dataSet = false;
		size_t _nElements = 0;
	};

}
