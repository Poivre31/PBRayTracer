module;
#include "OpenGL.h"
export module Core:Buffer;
import :Log;
namespace Vega {

	class SSBO
	{
	public:
		SSBO() {
			glGenBuffers(1, &_ID);
			_dataSet = false;
		}

		template <typename T>
		SSBO(T data[]) {
			glGenBuffers(1, &_ID);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data), data, GL_DYNAMIC_READ);
			_dataSet = true;
			_bufferSize = sizeof(data);
		}

		size_t GetReservedSize() const {
			return _bufferSize;
		}

		template <typename T>
		void SetData(T data[], size_t nElements) {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T) * nElements, data, GL_DYNAMIC_READ);
			_dataSet = true;
			_bufferSize = sizeof(T) * nElements;
		}

		template <typename T>
		void SetZero(T dataType, size_t nElements) {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T) * nElements, nullptr, GL_DYNAMIC_READ);
			_dataSet = true;
			_bufferSize = sizeof(T) * nElements;
		}

		void Bind(GLuint slot) const {
			if (!_dataSet) {
				Log.warn("Trying to bind SSBO whose data has not yet been set");
			}
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, _ID);
		}

		/// Updates a portion of the data on the GPU.
		/// Offset is in number of elements
		template <typename T>
		void UpdateData(T data[], size_t nElements, size_t offset = 0) {
			//if (!_dataSet) {
			//	Log::error("Trying to update SSBO whose data has not yet been set");
			//	return;
			//}
			//if (_bufferSize < offset + nElements * sizeof(T)) {
			//	Log::error("Trying to update SSBO with subdata larget than allocated size");
			//	return;
			//}
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset * sizeof(T), nElements * sizeof(T), data);
		}

		void Zero() {
			if (!_dataSet) {
				Log.error("Trying to zero SSBO whose data has not yet been set");
				return;
			}
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, _bufferSize, nullptr);
		}

		/// Gets data from the GPU.
		/// Offset is in number of elements
		template <typename T>
		void GetData(T data[], size_t nElements, size_t offset = 0) {
			if (!_dataSet) {
				Log.error("Trying to get data from SSBO whose data has not yet been set");
				return;
			}
			if (sizeof(data) < nElements * sizeof(T)) {
				Log.error("Trying to get data from SSBO into array smaller than the data");
				return;
			}
			glGetNamedBufferSubData(_ID, offset * sizeof(T), nElements * sizeof(T), &data);
		}

		void Reserve(size_t size) {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ID);
			glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_DYNAMIC_READ);
			_dataSet = true;
			_bufferSize = size;
		}

	private:
		GLuint _ID = 0;
		bool _dataSet = false;
		size_t _bufferSize = 0;
	};

}
