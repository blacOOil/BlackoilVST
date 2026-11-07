/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== Basic.vert ==================
static const unsigned char temp_binary_data_0[] =
"attribute vec4 position;\n"
"attribute vec4 sourceColour;\n"
"uniform mat4 projectionMatrix;\n"
"uniform mat4 viewMatrix;\n"
"varying vec4 destinationColour;\n"
"\n"
"void main()\n"
"{\n"
"    destinationColour = sourceColour;\n"
"    gl_Position = projectionMatrix * viewMatrix * position;\n"
"}\n";

const char* Basic_vert = (const char*) temp_binary_data_0;

//================== Basic.frag ==================
static const unsigned char temp_binary_data_1[] =
"varying vec4 destinationColour;\n"
"\n"
"void main()\n"
"{\n"
"    gl_FragColor = destinationColour;\n"
"}\n";

const char* Basic_frag = (const char*) temp_binary_data_1;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x33d45ac2:  numBytes = 257; return Basic_vert;
        case 0x33cd4383:  numBytes = 87; return Basic_frag;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "Basic_vert",
    "Basic_frag"
};

const char* originalFilenames[] =
{
    "Basic.vert",
    "Basic.frag"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
