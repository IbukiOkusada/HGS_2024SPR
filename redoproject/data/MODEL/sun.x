xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 125;
 0.00000;300.00000;0.00000;,
 129.90379;259.80759;-75.00000;,
 0.00000;259.80759;-150.00000;,
 129.90379;259.80759;75.00000;,
 0.00000;259.80759;150.00000;,
 -129.90379;259.80759;75.00000;,
 -129.90379;259.80759;-75.00000;,
 0.00000;259.80759;-150.00000;,
 129.90379;259.80759;-75.00000;,
 225.00000;150.00000;-129.90379;,
 0.00000;150.00000;-259.80759;,
 225.00000;150.00000;129.90379;,
 0.00000;150.00000;259.80759;,
 -225.00000;150.00000;129.90379;,
 -225.00000;150.00000;-129.90379;,
 0.00000;150.00000;-259.80759;,
 259.80759;0.00000;-150.00000;,
 0.00000;0.00000;-300.00000;,
 259.80759;-0.00000;150.00000;,
 -0.00000;0.00000;300.00000;,
 -259.80759;0.00000;150.00000;,
 -259.80759;0.00000;-150.00000;,
 0.00000;0.00000;-300.00000;,
 225.00000;-150.00000;-129.90379;,
 0.00000;-150.00000;-259.80759;,
 225.00000;-150.00000;129.90379;,
 -0.00000;-150.00000;259.80759;,
 -225.00000;-150.00000;129.90379;,
 -225.00000;-150.00000;-129.90379;,
 0.00000;-150.00000;-259.80759;,
 129.90379;-259.80759;-75.00000;,
 0.00000;-259.80759;-150.00000;,
 129.90379;-259.80759;75.00000;,
 -0.00000;-259.80759;150.00000;,
 -129.90379;-259.80759;75.00000;,
 -129.90379;-259.80759;-75.00000;,
 0.00000;-259.80759;-150.00000;,
 0.00000;-300.00000;-0.00000;,
 0.00000;-300.00000;-0.00000;,
 0.00000;437.47311;-100.00000;,
 0.00000;637.47302;0.00000;,
 70.71070;437.47311;-70.71070;,
 100.00000;437.47311;0.00000;,
 70.71070;437.47311;70.71070;,
 0.00000;637.47302;0.00000;,
 0.00000;437.47311;100.00000;,
 -70.71070;437.47311;70.71070;,
 -100.00000;437.47311;0.00000;,
 -70.71070;437.47311;-70.71070;,
 0.00000;437.47311;-100.00000;,
 0.00000;437.47311;0.00000;,
 70.71070;437.47311;-70.71070;,
 0.00000;-426.95529;-100.00000;,
 0.00000;-626.95538;0.00000;,
 -70.71070;-426.95529;-70.71070;,
 -70.71070;-426.95529;-70.71070;,
 0.00000;-626.95538;0.00000;,
 -100.00000;-426.95529;0.00000;,
 -70.71070;-426.95529;70.71070;,
 0.00000;-426.95529;100.00000;,
 70.71070;-426.95529;70.71070;,
 100.00000;-426.95529;-0.00000;,
 70.71070;-426.95529;-70.71070;,
 0.00000;-426.95529;-0.00000;,
 -100.00000;-426.95529;0.00000;,
 -442.65948;-7.57840;-100.00000;,
 -642.65979;-7.57840;0.00000;,
 -442.65948;63.13230;-70.71070;,
 -442.65948;92.42160;0.00000;,
 -442.65948;63.13230;70.71070;,
 -442.65948;-7.57840;100.00000;,
 -442.65948;-78.28910;70.71070;,
 -442.65948;-107.57840;0.00000;,
 -442.65948;-78.28910;-70.71070;,
 -442.65948;-7.57840;0.00000;,
 443.99469;-7.57840;-100.00000;,
 643.99481;-7.57840;-0.00000;,
 443.99469;-78.28900;-70.71070;,
 443.99469;-107.57840;0.00000;,
 443.99469;-78.28900;70.71070;,
 443.99469;-7.57840;100.00000;,
 443.99469;63.13230;70.71070;,
 443.99469;92.42160;0.00000;,
 443.99469;63.13230;-70.71070;,
 443.99469;-7.57840;-0.00000;,
 349.38309;-345.96661;-100.00000;,
 490.80460;-487.38809;-0.00000;,
 299.38309;-395.96661;-70.71070;,
 278.67239;-416.67719;0.00000;,
 299.38309;-395.96661;70.71070;,
 349.38309;-345.96661;100.00000;,
 399.38309;-295.96661;70.71070;,
 420.09381;-275.25601;-0.00000;,
 399.38309;-295.96661;-70.71070;,
 349.38309;-345.96661;-0.00000;,
 -330.28470;-364.73471;-100.00000;,
 -471.70621;-506.15619;0.00000;,
 -380.28470;-314.73480;-70.71070;,
 -400.99530;-294.02411;0.00000;,
 -380.28470;-314.73480;70.71070;,
 -330.28470;-364.73471;100.00000;,
 -280.28470;-414.73480;70.71070;,
 -259.57401;-435.44540;0.00000;,
 -280.28470;-414.73480;-70.71070;,
 -330.28470;-364.73471;0.00000;,
 -330.28470;313.97961;-100.00000;,
 -471.70609;455.40109;0.00000;,
 -280.28470;363.97961;-70.71070;,
 -259.57410;384.69019;0.00000;,
 -280.28470;363.97961;70.71070;,
 -330.28470;313.97961;100.00000;,
 -380.28479;263.97961;70.71070;,
 -400.99539;243.26900;0.00000;,
 -380.28479;263.97961;-70.71070;,
 -330.28470;313.97961;0.00000;,
 357.24881;313.97961;-100.00000;,
 498.67041;455.40109;0.00000;,
 407.24881;263.97961;-70.71070;,
 427.95941;243.26900;0.00000;,
 407.24881;263.97961;70.71070;,
 357.24881;313.97961;100.00000;,
 307.24881;363.97971;70.71070;,
 286.53821;384.69031;0.00000;,
 307.24881;363.97971;-70.71070;,
 357.24881;313.97961;0.00000;;
 
 164;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,2,6;,
 4;7,8,9,10;,
 4;8,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,2,15,14;,
 4;10,9,16,17;,
 4;9,11,18,16;,
 4;11,12,19,18;,
 4;12,13,20,19;,
 4;13,14,21,20;,
 4;14,15,22,21;,
 4;17,16,23,24;,
 4;16,18,25,23;,
 4;18,19,26,25;,
 4;19,20,27,26;,
 4;20,21,28,27;,
 4;21,22,29,28;,
 4;24,23,30,31;,
 4;23,25,32,30;,
 4;25,26,33,32;,
 4;26,27,34,33;,
 4;27,28,35,34;,
 4;28,29,36,35;,
 3;31,30,37;,
 3;30,32,37;,
 3;32,33,38;,
 3;33,34,38;,
 3;34,35,38;,
 3;35,36,38;,
 3;39,40,41;,
 3;41,40,42;,
 3;42,40,43;,
 3;43,44,45;,
 3;45,44,46;,
 3;46,44,47;,
 3;47,44,48;,
 3;48,44,49;,
 3;50,49,51;,
 3;50,51,42;,
 3;50,42,43;,
 3;50,43,45;,
 3;50,45,46;,
 3;50,46,47;,
 3;50,47,48;,
 3;50,48,49;,
 3;52,53,54;,
 3;55,56,57;,
 3;57,56,58;,
 3;58,56,59;,
 3;59,56,60;,
 3;60,56,61;,
 3;61,53,62;,
 3;62,53,52;,
 3;63,52,54;,
 3;63,54,64;,
 3;63,64,58;,
 3;63,58,59;,
 3;63,59,60;,
 3;63,60,61;,
 3;63,61,62;,
 3;63,62,52;,
 3;65,66,67;,
 3;67,66,68;,
 3;68,66,69;,
 3;69,66,70;,
 3;70,66,71;,
 3;71,66,72;,
 3;72,66,73;,
 3;73,66,65;,
 3;74,65,67;,
 3;74,67,68;,
 3;74,68,69;,
 3;74,69,70;,
 3;74,70,71;,
 3;74,71,72;,
 3;74,72,73;,
 3;74,73,65;,
 3;75,76,77;,
 3;77,76,78;,
 3;78,76,79;,
 3;79,76,80;,
 3;80,76,81;,
 3;81,76,82;,
 3;82,76,83;,
 3;83,76,75;,
 3;84,75,77;,
 3;84,77,78;,
 3;84,78,79;,
 3;84,79,80;,
 3;84,80,81;,
 3;84,81,82;,
 3;84,82,83;,
 3;84,83,75;,
 3;85,86,87;,
 3;87,86,88;,
 3;88,86,89;,
 3;89,86,90;,
 3;90,86,91;,
 3;91,86,92;,
 3;92,86,93;,
 3;93,86,85;,
 3;94,85,87;,
 3;94,87,88;,
 3;94,88,89;,
 3;94,89,90;,
 3;94,90,91;,
 3;94,91,92;,
 3;94,92,93;,
 3;94,93,85;,
 3;95,96,97;,
 3;97,96,98;,
 3;98,96,99;,
 3;99,96,100;,
 3;100,96,101;,
 3;101,96,102;,
 3;102,96,103;,
 3;103,96,95;,
 3;104,95,97;,
 3;104,97,98;,
 3;104,98,99;,
 3;104,99,100;,
 3;104,100,101;,
 3;104,101,102;,
 3;104,102,103;,
 3;104,103,95;,
 3;105,106,107;,
 3;107,106,108;,
 3;108,106,109;,
 3;109,106,110;,
 3;110,106,111;,
 3;111,106,112;,
 3;112,106,113;,
 3;113,106,105;,
 3;114,105,107;,
 3;114,107,108;,
 3;114,108,109;,
 3;114,109,110;,
 3;114,110,111;,
 3;114,111,112;,
 3;114,112,113;,
 3;114,113,105;,
 3;115,116,117;,
 3;117,116,118;,
 3;118,116,119;,
 3;119,116,120;,
 3;120,116,121;,
 3;121,116,122;,
 3;122,116,123;,
 3;123,116,115;,
 3;124,115,117;,
 3;124,117,118;,
 3;124,118,119;,
 3;124,119,120;,
 3;124,120,121;,
 3;124,121,122;,
 3;124,122,123;,
 3;124,123,115;;
 
 MeshMaterialList {
  2;
  164;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.480000;0.480000;0.480000;;
   TextureFilename {
    "data\\TEXTURE\\sun.png";
   }
  }
  Material {
   0.800000;0.354400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  128;
  0.000000;1.000000;0.000000;,
  0.000000;0.870413;-0.492322;,
  0.426363;0.870413;-0.246161;,
  0.426363;0.870413;0.246161;,
  0.000000;0.870413;0.492322;,
  -0.426363;0.870413;0.246161;,
  -0.426363;0.870413;-0.246161;,
  0.000000;0.506749;-0.862093;,
  0.746595;0.506749;-0.431047;,
  0.746595;0.506749;0.431047;,
  0.000000;0.506749;0.862093;,
  -0.746595;0.506749;0.431047;,
  -0.746595;0.506749;-0.431047;,
  0.000000;0.000000;-1.000000;,
  0.866025;0.000000;-0.500000;,
  0.866025;0.000000;0.500000;,
  0.000000;0.000000;1.000000;,
  -0.866025;0.000000;0.500000;,
  -0.866025;0.000000;-0.500000;,
  0.000000;-0.506749;-0.862093;,
  0.746595;-0.506749;-0.431047;,
  0.746595;-0.506749;0.431047;,
  0.000000;-0.506749;0.862093;,
  -0.746595;-0.506749;0.431047;,
  -0.746595;-0.506749;-0.431047;,
  0.000000;-0.870413;-0.492322;,
  0.426363;-0.870413;-0.246161;,
  0.426363;-0.870413;0.246161;,
  0.000000;-0.870413;0.492322;,
  -0.426363;-0.870413;0.246161;,
  -0.426363;-0.870413;-0.246161;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.447214;-0.894427;,
  0.632455;0.447214;-0.632455;,
  0.894427;0.447214;0.000000;,
  0.632455;0.447214;0.632455;,
  0.000000;0.447214;0.894427;,
  -0.632455;0.447214;0.632455;,
  -0.894427;0.447214;0.000000;,
  -0.632455;0.447214;-0.632455;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.447213;-0.894427;,
  -0.632456;-0.447214;-0.632456;,
  -0.894427;-0.447213;0.000000;,
  -0.632456;-0.447214;0.632456;,
  0.000000;-0.447213;0.894427;,
  0.632456;-0.447214;0.632456;,
  0.894427;-0.447213;-0.000000;,
  0.632456;-0.447214;-0.632456;,
  0.000000;1.000000;0.000000;,
  -0.447213;0.000000;-0.894427;,
  -0.447213;0.632456;-0.632456;,
  -0.447213;0.894427;0.000000;,
  -0.447213;0.632456;0.632456;,
  -0.447213;0.000000;0.894427;,
  -0.447213;-0.632456;0.632456;,
  -0.447213;-0.894427;0.000000;,
  -0.447213;-0.632456;-0.632456;,
  1.000000;0.000000;0.000000;,
  0.447213;-0.000000;-0.894427;,
  0.447213;-0.632455;-0.632456;,
  0.447213;-0.894427;-0.000000;,
  0.447213;-0.632455;0.632456;,
  0.447213;-0.000000;0.894427;,
  0.447214;0.632456;0.632456;,
  0.447213;0.894427;0.000000;,
  0.447214;0.632456;-0.632456;,
  -1.000000;0.000000;0.000000;,
  0.316228;-0.316228;-0.894427;,
  -0.130986;-0.763442;-0.632455;,
  -0.316228;-0.948683;0.000000;,
  -0.130986;-0.763442;0.632455;,
  0.316228;-0.316228;0.894427;,
  0.763441;0.130986;0.632456;,
  0.948683;0.316228;0.000000;,
  0.763441;0.130986;-0.632456;,
  -0.707107;0.707107;0.000000;,
  -0.707107;0.707107;0.000000;,
  -0.707107;0.707107;-0.000000;,
  -0.707106;0.707107;0.000000;,
  -0.707107;0.707107;0.000000;,
  -0.707106;0.707107;-0.000000;,
  -0.707106;0.707107;0.000000;,
  -0.316228;-0.316227;-0.894427;,
  -0.763441;0.130986;-0.632455;,
  -0.948683;0.316229;0.000000;,
  -0.763441;0.130986;0.632455;,
  -0.316228;-0.316227;0.894427;,
  0.130986;-0.763441;0.632456;,
  0.316228;-0.948683;-0.000000;,
  0.130986;-0.763441;-0.632456;,
  0.707107;0.707107;0.000000;,
  0.707106;0.707107;-0.000000;,
  0.707106;0.707107;0.000000;,
  0.707107;0.707106;0.000000;,
  0.707107;0.707106;-0.000000;,
  -0.316227;0.316228;-0.894427;,
  0.130986;0.763442;-0.632455;,
  0.316229;0.948683;0.000000;,
  0.130986;0.763442;0.632455;,
  -0.316227;0.316228;0.894427;,
  -0.763442;-0.130986;0.632455;,
  -0.948683;-0.316228;0.000000;,
  -0.763442;-0.130986;-0.632455;,
  0.707107;-0.707107;-0.000000;,
  0.707106;-0.707107;-0.000000;,
  0.707107;-0.707107;-0.000000;,
  0.707107;-0.707107;-0.000000;,
  0.707107;-0.707107;0.000000;,
  0.707106;-0.707107;0.000000;,
  0.707106;-0.707107;-0.000000;,
  0.707106;-0.707107;-0.000000;,
  0.316228;0.316227;-0.894427;,
  0.763441;-0.130987;-0.632455;,
  0.948683;-0.316229;-0.000000;,
  0.763441;-0.130987;0.632455;,
  0.316228;0.316227;0.894427;,
  -0.130986;0.763442;0.632455;,
  -0.316228;0.948683;0.000000;,
  -0.130986;0.763442;-0.632455;,
  -0.707107;-0.707107;0.000000;,
  -0.707107;-0.707106;0.000000;,
  -0.707107;-0.707107;-0.000000;,
  -0.707107;-0.707107;0.000000;,
  -0.707107;-0.707107;0.000000;,
  -0.707107;-0.707106;0.000000;,
  -0.707107;-0.707106;0.000000;,
  -0.707107;-0.707106;-0.000000;;
  164;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,6,12,11;,
  4;6,1,7,12;,
  4;7,8,14,13;,
  4;8,9,15,14;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,12,18,17;,
  4;12,7,13,18;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,18,24,23;,
  4;18,13,19,24;,
  4;19,20,26,25;,
  4;20,21,27,26;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,24,30,29;,
  4;24,19,25,30;,
  3;25,26,31;,
  3;26,27,31;,
  3;27,28,31;,
  3;28,29,31;,
  3;29,30,31;,
  3;30,25,31;,
  3;32,33,33;,
  3;33,33,34;,
  3;34,35,35;,
  3;35,35,36;,
  3;36,37,37;,
  3;37,37,38;,
  3;38,39,39;,
  3;39,39,32;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;41,42,42;,
  3;42,42,43;,
  3;43,44,44;,
  3;44,44,45;,
  3;45,46,46;,
  3;46,46,47;,
  3;47,48,48;,
  3;48,48,41;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;50,51,51;,
  3;51,51,52;,
  3;52,53,53;,
  3;53,53,54;,
  3;54,55,55;,
  3;55,55,56;,
  3;56,57,57;,
  3;57,57,50;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;59,60,60;,
  3;60,60,61;,
  3;61,62,62;,
  3;62,62,63;,
  3;63,64,64;,
  3;64,64,65;,
  3;65,66,66;,
  3;66,66,59;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;68,69,69;,
  3;69,69,70;,
  3;70,71,71;,
  3;71,71,72;,
  3;72,73,73;,
  3;73,73,74;,
  3;74,75,75;,
  3;75,75,68;,
  3;76,77,78;,
  3;76,78,79;,
  3;76,79,80;,
  3;76,80,77;,
  3;76,77,81;,
  3;76,81,79;,
  3;76,79,82;,
  3;76,82,77;,
  3;83,84,84;,
  3;84,84,85;,
  3;85,86,86;,
  3;86,86,87;,
  3;87,88,88;,
  3;88,88,89;,
  3;89,90,90;,
  3;90,90,83;,
  3;91,91,92;,
  3;91,92,91;,
  3;91,91,93;,
  3;91,93,91;,
  3;91,91,94;,
  3;91,94,91;,
  3;91,91,95;,
  3;91,95,91;,
  3;96,97,97;,
  3;97,97,98;,
  3;98,99,99;,
  3;99,99,100;,
  3;100,101,101;,
  3;101,101,102;,
  3;102,103,103;,
  3;103,103,96;,
  3;104,105,106;,
  3;104,106,107;,
  3;104,107,108;,
  3;104,108,105;,
  3;104,105,109;,
  3;104,109,110;,
  3;104,110,111;,
  3;104,111,105;,
  3;112,113,113;,
  3;113,113,114;,
  3;114,115,115;,
  3;115,115,116;,
  3;116,117,117;,
  3;117,117,118;,
  3;118,119,119;,
  3;119,119,112;,
  3;120,121,122;,
  3;120,122,123;,
  3;120,123,124;,
  3;120,124,121;,
  3;120,121,125;,
  3;120,125,126;,
  3;120,126,127;,
  3;120,127,121;;
 }
 MeshTextureCoords {
  125;
  0.750000;0.000000;,
  1.166667;0.166667;,
  1.000000;0.166667;,
  0.333333;0.166667;,
  0.500000;0.166667;,
  0.666667;0.166667;,
  0.833333;0.166667;,
  0.000000;0.166667;,
  0.166667;0.166667;,
  0.166667;0.333333;,
  0.000000;0.333333;,
  0.333333;0.333333;,
  0.500000;0.333333;,
  0.666667;0.333333;,
  0.833333;0.333333;,
  1.000000;0.333333;,
  0.166667;0.500000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.500000;0.500000;,
  0.666667;0.500000;,
  0.833333;0.500000;,
  1.000000;0.500000;,
  0.166667;0.666667;,
  0.000000;0.666667;,
  0.333333;0.666667;,
  0.500000;0.666667;,
  0.666667;0.666667;,
  0.833333;0.666667;,
  1.000000;0.666667;,
  0.166667;0.833333;,
  0.000000;0.833333;,
  0.333333;0.833333;,
  0.500000;0.833333;,
  0.666667;0.833333;,
  0.833333;0.833333;,
  1.000000;0.833333;,
  -0.250000;1.000000;,
  0.750000;1.000000;,
  0.000000;0.071530;,
  -0.250000;0.000000;,
  0.125000;0.071530;,
  0.250000;0.071530;,
  0.375000;0.071530;,
  0.750000;0.000000;,
  0.500000;0.071530;,
  0.625000;0.071530;,
  0.750000;0.071530;,
  0.875000;0.071530;,
  1.000000;0.071530;,
  0.750000;0.000000;,
  1.125000;0.071530;,
  0.000000;0.926770;,
  -0.250000;1.000000;,
  -0.125000;0.926770;,
  0.875000;0.926770;,
  0.750000;1.000000;,
  0.750000;0.926770;,
  0.625000;0.926770;,
  0.500000;0.926770;,
  0.375000;0.926770;,
  0.250000;0.926770;,
  0.125000;0.926770;,
  0.250000;1.000000;,
  -0.250000;0.926770;,
  0.783960;0.505110;,
  0.750000;0.503650;,
  0.774200;0.457210;,
  0.750000;0.437080;,
  0.725800;0.457210;,
  0.716040;0.505110;,
  0.725800;0.552890;,
  0.750000;0.572900;,
  0.774200;0.552890;,
  0.750000;0.505230;,
  0.217890;0.504830;,
  0.250000;0.503500;,
  0.227140;0.550030;,
  0.250000;0.568940;,
  0.272860;0.550030;,
  0.282110;0.504830;,
  0.272860;0.459540;,
  0.250000;0.440530;,
  0.227140;0.459540;,
  0.250000;0.504930;,
  0.217890;0.504830;,
  0.250000;0.503500;,
  0.227140;0.550030;,
  0.250000;0.568940;,
  0.272860;0.550030;,
  0.282110;0.504830;,
  0.272860;0.459540;,
  0.250000;0.440530;,
  0.227140;0.459540;,
  0.250000;0.504930;,
  0.217890;0.504830;,
  0.250000;0.503500;,
  0.227140;0.550030;,
  0.250000;0.568940;,
  0.272860;0.550030;,
  0.282110;0.504830;,
  0.272860;0.459540;,
  0.250000;0.440530;,
  0.227140;0.459540;,
  0.250000;0.504930;,
  0.217890;0.504830;,
  0.250000;0.503500;,
  0.227140;0.550030;,
  0.250000;0.568940;,
  0.272860;0.550030;,
  0.282110;0.504830;,
  0.272860;0.459540;,
  0.250000;0.440530;,
  0.227140;0.459540;,
  0.250000;0.504930;,
  0.217890;0.504830;,
  0.250000;0.503500;,
  0.227140;0.550030;,
  0.250000;0.568940;,
  0.272860;0.550030;,
  0.282110;0.504830;,
  0.272860;0.459540;,
  0.250000;0.440530;,
  0.227140;0.459540;,
  0.250000;0.504930;;
 }
}
