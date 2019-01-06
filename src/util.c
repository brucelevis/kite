#include "util.h"
#include "common.h"
#define STB_IMAGE_IMPLEMENTATION


int filesize(FILE*stream)
{
	int curpos, length;
	
	curpos = ftell(stream);
	fseek(stream, 0L, SEEK_END);
	
	length = ftell(stream);
	fseek(stream, curpos, SEEK_SET);
	return length;
}

char * readfile(const char* name, int *sz) {
	FILE *fp = fopen(name, "rb");
	if (!fp) {
		fprintf(stderr, "failed to open file: %s\n", name);
		exit(1);
	}

	int size = filesize(fp);
	char *data = malloc(size);

	fread(data, size, 1, fp);

	if (sz) {
		*sz = size;
	}

	fclose(fp);

	return data;
}


GLuint create_shader(const char* file, GLenum type) {
	GLuint shader = glCreateShader(type);
	ASSERT(shader != 0, "failed to create shader\n");

	GLint sz;
	const char * text = readfile(file, &sz);
	glShaderSource(shader, 1, &text, &sz);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar info[1024];
		glGetShaderInfoLog(shader, 1024, NULL, info);
		fprintf(stderr, "faield to compile shader[%s] type:%d, '%s'\n", file, type, info);
		exit(1);
	}
	return shader;
}

GLuint
program_from_file(const char *vs_name, const char *fs_name) {
	GLuint vs = create_shader(vs_name, GL_VERTEX_SHADER);
	GLuint fs = create_shader(fs_name, GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
	glLinkProgram(program);

	GLint success = 0;
	GLchar err_info[1024] = { 0 };
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, sizeof(err_info), NULL, err_info);
		fprintf(stderr, "failed to link shader program: '%s'\n", err_info);
		exit(1);
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}


void
mat4x4_ortho(mat4x4 M, float l, float r, float b, float t, float n, float f) {
	M[0][0] = 2.f / (r - l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;

	M[1][1] = 2.f / (t - b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][2] = -2.f / (f - n);
	M[2][0] = M[2][1] = M[2][3] = 0.f;

	M[3][0] = -(r + l) / (r - l);
	M[3][1] = -(t + b) / (t - b);
	M[3][2] = -(f + n) / (f - n);
	M[3][3] = 1.f;
}


unsigned char *
load_image(const char *filename, int *width, int *height, int *channel, bool flip_vertically) {
	stbi_set_flip_vertically_on_load(flip_vertically);
	return stbi_load(filename, width, height, channel, STBI_rgb_alpha);
}