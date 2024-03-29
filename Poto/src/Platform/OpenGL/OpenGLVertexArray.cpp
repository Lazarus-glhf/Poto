#include "ptpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Poto {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Poto::ShaderDataType::Float:    return GL_FLOAT;
		case Poto::ShaderDataType::Float2:   return GL_FLOAT;
		case Poto::ShaderDataType::Float3:   return GL_FLOAT;
		case Poto::ShaderDataType::Float4:   return GL_FLOAT;
		case Poto::ShaderDataType::Mat3:     return GL_FLOAT;
		case Poto::ShaderDataType::Mat4:     return GL_FLOAT;
		case Poto::ShaderDataType::Int:      return GL_INT;
		case Poto::ShaderDataType::Int2:     return GL_INT;
		case Poto::ShaderDataType::Int3:     return GL_INT;
		case Poto::ShaderDataType::Int4:     return GL_INT;
		case Poto::ShaderDataType::Bool:     return GL_BOOL;
		}

		PT_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		PT_PROFILE_FUNCTION()

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		PT_PROFILE_FUNCTION()

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		PT_PROFILE_FUNCTION()

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		PT_PROFILE_FUNCTION()

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		PT_PROFILE_FUNCTION()

		PT_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		PT_PROFILE_FUNCTION()

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}