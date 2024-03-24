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
 92;
 -8.44623;1.07031;-1.47315;,
 -8.44623;1.73181;-0.56268;,
 -7.60926;3.29406;-1.07031;,
 -7.60926;2.03586;-2.80209;,
 -8.44623;1.73181;0.56268;,
 -7.60926;3.29406;1.07031;,
 -8.44623;1.07031;1.47315;,
 -7.60926;2.03586;2.80209;,
 -8.44623;0.00000;1.82091;,
 -7.60926;0.00000;3.46356;,
 -8.44623;-1.07028;1.47315;,
 -7.60926;-2.03583;2.80209;,
 -8.44623;-1.73178;0.56268;,
 -7.60926;-3.29403;1.07031;,
 -8.44623;-1.73178;-0.56268;,
 -7.60926;-3.29403;-1.07031;,
 -8.44623;-1.07028;-1.47315;,
 -7.60926;-2.03583;-2.80209;,
 -8.44623;0.00000;-1.82091;,
 -7.60926;0.00000;-3.46356;,
 -6.30561;4.53387;-1.47315;,
 -6.30561;2.80209;-3.85674;,
 -6.30561;4.53387;1.47315;,
 -6.30561;2.80209;3.85674;,
 -6.30561;0.00000;4.76721;,
 -6.30561;-2.80209;3.85674;,
 -6.30561;-4.53387;1.47315;,
 -6.30561;-4.53387;-1.47315;,
 -6.30561;-2.80209;-3.85674;,
 -6.30561;0.00000;-4.76721;,
 -4.66296;5.32989;-1.73178;,
 -4.66296;3.29406;-4.53387;,
 -4.66296;5.32989;1.73178;,
 -4.66296;3.29406;4.53387;,
 -4.66296;0.00000;5.60418;,
 -4.66296;-3.29403;4.53387;,
 -4.66296;-5.32989;1.73178;,
 -4.66296;-5.32989;-1.73178;,
 -4.66296;-3.29403;-4.53387;,
 -4.66296;0.00000;-5.60418;,
 -2.84205;5.60418;-1.82091;,
 -2.84205;3.46359;-4.76721;,
 -2.84205;5.60418;1.82091;,
 -2.84205;3.46359;4.76721;,
 -2.84205;0.00000;5.89257;,
 -2.84205;-3.46356;4.76721;,
 -2.84205;-5.60418;1.82091;,
 -2.84205;-5.60418;-1.82091;,
 -2.84205;-3.46356;-4.76721;,
 -2.84205;0.00000;-5.89257;,
 -1.02114;5.32989;-1.73178;,
 -1.02114;3.29406;-4.53387;,
 -1.02114;5.32989;1.73178;,
 -1.02114;3.29406;4.53387;,
 -1.02114;0.00000;5.60418;,
 -1.02114;-3.29403;4.53387;,
 -1.02114;-5.32989;1.73178;,
 -1.02114;-5.32989;-1.73178;,
 -1.02114;-3.29403;-4.53387;,
 -1.02114;0.00000;-5.60418;,
 0.62151;4.53387;-1.47315;,
 0.62151;2.80209;-3.85674;,
 0.62151;4.53387;1.47315;,
 0.62151;2.80209;3.85674;,
 0.62151;0.00000;4.76721;,
 0.62151;-2.80209;3.85674;,
 0.62151;-4.53387;1.47315;,
 0.62151;-4.53387;-1.47315;,
 0.62151;-2.80209;-3.85674;,
 0.62151;0.00000;-4.76721;,
 1.92516;3.29406;-1.07031;,
 1.92516;2.03586;-2.80209;,
 1.92516;3.29406;1.07031;,
 1.92516;2.03586;2.80209;,
 1.92516;0.00000;3.46356;,
 1.92516;-2.03583;2.80209;,
 1.92516;-3.29403;1.07031;,
 1.92516;-3.29403;-1.07031;,
 1.92516;-2.03583;-2.80209;,
 1.92516;0.00000;-3.46356;,
 2.76213;1.73181;-0.56268;,
 2.76213;1.07031;-1.47315;,
 2.76213;1.73181;0.56268;,
 2.76213;1.07031;1.47315;,
 2.76213;0.00000;1.82091;,
 2.76213;-1.07028;1.47315;,
 2.76213;-1.73178;0.56268;,
 2.76213;-1.73178;-0.56268;,
 2.76213;-1.07028;-1.47315;,
 2.76213;0.00000;-1.82091;,
 -8.73462;0.00000;0.00000;,
 3.05052;0.00000;0.00000;;
 
 100;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,0,3,19;,
 4;3,2,20,21;,
 4;2,5,22,20;,
 4;5,7,23,22;,
 4;7,9,24,23;,
 4;9,11,25,24;,
 4;11,13,26,25;,
 4;13,15,27,26;,
 4;15,17,28,27;,
 4;17,19,29,28;,
 4;19,3,21,29;,
 4;21,20,30,31;,
 4;20,22,32,30;,
 4;22,23,33,32;,
 4;23,24,34,33;,
 4;24,25,35,34;,
 4;25,26,36,35;,
 4;26,27,37,36;,
 4;27,28,38,37;,
 4;28,29,39,38;,
 4;29,21,31,39;,
 4;31,30,40,41;,
 4;30,32,42,40;,
 4;32,33,43,42;,
 4;33,34,44,43;,
 4;34,35,45,44;,
 4;35,36,46,45;,
 4;36,37,47,46;,
 4;37,38,48,47;,
 4;38,39,49,48;,
 4;39,31,41,49;,
 4;41,40,50,51;,
 4;40,42,52,50;,
 4;42,43,53,52;,
 4;43,44,54,53;,
 4;44,45,55,54;,
 4;45,46,56,55;,
 4;46,47,57,56;,
 4;47,48,58,57;,
 4;48,49,59,58;,
 4;49,41,51,59;,
 4;51,50,60,61;,
 4;50,52,62,60;,
 4;52,53,63,62;,
 4;53,54,64,63;,
 4;54,55,65,64;,
 4;55,56,66,65;,
 4;56,57,67,66;,
 4;57,58,68,67;,
 4;58,59,69,68;,
 4;59,51,61,69;,
 4;61,60,70,71;,
 4;60,62,72,70;,
 4;62,63,73,72;,
 4;63,64,74,73;,
 4;64,65,75,74;,
 4;65,66,76,75;,
 4;66,67,77,76;,
 4;67,68,78,77;,
 4;68,69,79,78;,
 4;69,61,71,79;,
 4;71,70,80,81;,
 4;70,72,82,80;,
 4;72,73,83,82;,
 4;73,74,84,83;,
 4;74,75,85,84;,
 4;75,76,86,85;,
 4;76,77,87,86;,
 4;77,78,88,87;,
 4;78,79,89,88;,
 4;79,71,81,89;,
 3;1,0,90;,
 3;4,1,90;,
 3;6,4,90;,
 3;8,6,90;,
 3;10,8,90;,
 3;12,10,90;,
 3;14,12,90;,
 3;16,14,90;,
 3;18,16,90;,
 3;0,18,90;,
 3;81,80,91;,
 3;80,82,91;,
 3;82,83,91;,
 3;83,84,91;,
 3;84,85,91;,
 3;85,86,91;,
 3;86,87,91;,
 3;87,88,91;,
 3;88,89,91;,
 3;89,81,91;;
 
 MeshMaterialList {
  1;
  100;
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\kids_girl_UV.png";
   }
  }
 }
 MeshNormals {
  92;
  -0.951290;0.181212;-0.249419;,
  -0.951290;0.293209;-0.095269;,
  -0.951290;0.293209;0.095269;,
  -0.951290;0.181212;0.249419;,
  -0.951289;-0.000001;0.308299;,
  -0.951290;-0.181213;0.249419;,
  -0.951289;-0.293210;0.095270;,
  -0.951289;-0.293210;-0.095270;,
  -0.951290;-0.181213;-0.249419;,
  -0.951290;-0.000001;-0.308299;,
  -0.809711;0.344929;-0.474755;,
  -0.809709;0.558110;-0.181340;,
  -0.809709;0.558110;0.181340;,
  -0.809711;0.344929;0.474755;,
  -0.809712;-0.000001;0.586828;,
  -0.809712;-0.344928;0.474753;,
  -0.809712;-0.558106;0.181339;,
  -0.809712;-0.558106;-0.181339;,
  -0.809712;-0.344928;-0.474753;,
  -0.809712;-0.000001;-0.586828;,
  -0.588712;0.475133;-0.653962;,
  -0.588711;0.768780;-0.249792;,
  -0.588711;0.768780;0.249792;,
  -0.588712;0.475133;0.653962;,
  -0.588714;-0.000001;0.808342;,
  -0.588713;-0.475132;0.653962;,
  -0.588715;-0.768778;0.249792;,
  -0.588715;-0.768778;-0.249792;,
  -0.588713;-0.475132;-0.653962;,
  -0.588714;-0.000001;-0.808342;,
  -0.309681;0.558891;-0.769246;,
  -0.309682;0.904303;-0.293825;,
  -0.309682;0.904303;0.293825;,
  -0.309681;0.558891;0.769246;,
  -0.309679;-0.000001;0.950841;,
  -0.309679;-0.558890;0.769247;,
  -0.309680;-0.904303;0.293828;,
  -0.309680;-0.904303;-0.293828;,
  -0.309679;-0.558890;-0.769247;,
  -0.309679;-0.000001;-0.950841;,
  0.000000;0.587785;-0.809017;,
  0.000000;0.951057;-0.309015;,
  0.000000;0.951057;0.309015;,
  0.000000;0.587785;0.809017;,
  -0.000000;-0.000001;1.000000;,
  -0.000000;-0.587784;0.809018;,
  -0.000000;-0.951056;0.309018;,
  -0.000000;-0.951056;-0.309018;,
  -0.000000;-0.587784;-0.809018;,
  -0.000000;-0.000001;-1.000000;,
  0.309681;0.558891;-0.769246;,
  0.309682;0.904303;-0.293825;,
  0.309682;0.904303;0.293825;,
  0.309681;0.558891;0.769246;,
  0.309678;-0.000001;0.950841;,
  0.309678;-0.558890;0.769247;,
  0.309680;-0.904303;0.293828;,
  0.309680;-0.904303;-0.293828;,
  0.309678;-0.558890;-0.769247;,
  0.309678;-0.000001;-0.950841;,
  0.588712;0.475133;-0.653962;,
  0.588711;0.768780;-0.249791;,
  0.588711;0.768780;0.249791;,
  0.588712;0.475133;0.653962;,
  0.588713;-0.000001;0.808342;,
  0.588712;-0.475133;0.653963;,
  0.588715;-0.768778;0.249792;,
  0.588715;-0.768778;-0.249792;,
  0.588712;-0.475133;-0.653963;,
  0.588713;-0.000001;-0.808342;,
  0.809711;0.344929;-0.474755;,
  0.809709;0.558110;-0.181340;,
  0.809709;0.558110;0.181340;,
  0.809711;0.344929;0.474755;,
  0.809712;-0.000001;0.586828;,
  0.809712;-0.344928;0.474753;,
  0.809712;-0.558106;0.181339;,
  0.809712;-0.558106;-0.181339;,
  0.809712;-0.344929;-0.474753;,
  0.809712;-0.000001;-0.586828;,
  0.951290;0.181212;-0.249419;,
  0.951290;0.293209;-0.095269;,
  0.951290;0.293209;0.095269;,
  0.951290;0.181212;0.249419;,
  0.951290;-0.000001;0.308299;,
  0.951290;-0.181213;0.249419;,
  0.951289;-0.293210;0.095269;,
  0.951289;-0.293210;-0.095269;,
  0.951290;-0.181213;-0.249419;,
  0.951290;-0.000001;-0.308299;,
  -1.000000;-0.000001;0.000000;,
  1.000000;-0.000001;0.000000;;
  100;
  4;0,1,11,10;,
  4;1,2,12,11;,
  4;2,3,13,12;,
  4;3,4,14,13;,
  4;4,5,15,14;,
  4;5,6,16,15;,
  4;6,7,17,16;,
  4;7,8,18,17;,
  4;8,9,19,18;,
  4;9,0,10,19;,
  4;10,11,21,20;,
  4;11,12,22,21;,
  4;12,13,23,22;,
  4;13,14,24,23;,
  4;14,15,25,24;,
  4;15,16,26,25;,
  4;16,17,27,26;,
  4;17,18,28,27;,
  4;18,19,29,28;,
  4;19,10,20,29;,
  4;20,21,31,30;,
  4;21,22,32,31;,
  4;22,23,33,32;,
  4;23,24,34,33;,
  4;24,25,35,34;,
  4;25,26,36,35;,
  4;26,27,37,36;,
  4;27,28,38,37;,
  4;28,29,39,38;,
  4;29,20,30,39;,
  4;30,31,41,40;,
  4;31,32,42,41;,
  4;32,33,43,42;,
  4;33,34,44,43;,
  4;34,35,45,44;,
  4;35,36,46,45;,
  4;36,37,47,46;,
  4;37,38,48,47;,
  4;38,39,49,48;,
  4;39,30,40,49;,
  4;40,41,51,50;,
  4;41,42,52,51;,
  4;42,43,53,52;,
  4;43,44,54,53;,
  4;44,45,55,54;,
  4;45,46,56,55;,
  4;46,47,57,56;,
  4;47,48,58,57;,
  4;48,49,59,58;,
  4;49,40,50,59;,
  4;50,51,61,60;,
  4;51,52,62,61;,
  4;52,53,63,62;,
  4;53,54,64,63;,
  4;54,55,65,64;,
  4;55,56,66,65;,
  4;56,57,67,66;,
  4;57,58,68,67;,
  4;58,59,69,68;,
  4;59,50,60,69;,
  4;60,61,71,70;,
  4;61,62,72,71;,
  4;62,63,73,72;,
  4;63,64,74,73;,
  4;64,65,75,74;,
  4;65,66,76,75;,
  4;66,67,77,76;,
  4;67,68,78,77;,
  4;68,69,79,78;,
  4;69,60,70,79;,
  4;70,71,81,80;,
  4;71,72,82,81;,
  4;72,73,83,82;,
  4;73,74,84,83;,
  4;74,75,85,84;,
  4;75,76,86,85;,
  4;76,77,87,86;,
  4;77,78,88,87;,
  4;78,79,89,88;,
  4;79,70,80,89;,
  3;1,0,90;,
  3;2,1,90;,
  3;3,2,90;,
  3;4,3,90;,
  3;5,4,90;,
  3;6,5,90;,
  3;7,6,90;,
  3;8,7,90;,
  3;9,8,90;,
  3;0,9,90;,
  3;80,81,91;,
  3;81,82,91;,
  3;82,83,91;,
  3;83,84,91;,
  3;84,85,91;,
  3;85,86,91;,
  3;86,87,91;,
  3;87,88,91;,
  3;88,89,91;,
  3;89,80,91;;
 }
 MeshTextureCoords {
  92;
  0.209155;0.760547;,
  0.201970;0.755058;,
  0.205976;0.742096;,
  0.219641;0.752536;,
  0.193090;0.755058;,
  0.189084;0.742096;,
  0.185905;0.760547;,
  0.175419;0.752536;,
  0.183161;0.769427;,
  0.170199;0.769427;,
  0.185905;0.778307;,
  0.175419;0.786318;,
  0.193090;0.783796;,
  0.189084;0.796758;,
  0.201970;0.783796;,
  0.205976;0.796758;,
  0.209155;0.778307;,
  0.219641;0.786318;,
  0.211899;0.769427;,
  0.224861;0.769427;,
  0.209155;0.731809;,
  0.227963;0.746178;,
  0.185905;0.731809;,
  0.167097;0.746178;,
  0.159912;0.769427;,
  0.167097;0.792676;,
  0.185905;0.807045;,
  0.209155;0.807045;,
  0.227963;0.792676;,
  0.235148;0.769427;,
  0.211195;0.725205;,
  0.233307;0.742096;,
  0.183865;0.725205;,
  0.161753;0.742096;,
  0.153308;0.769427;,
  0.161753;0.796758;,
  0.183865;0.813649;,
  0.211195;0.813649;,
  0.233307;0.796758;,
  0.241752;0.769427;,
  0.211899;0.722929;,
  0.235148;0.740690;,
  0.183161;0.722929;,
  0.159912;0.740690;,
  0.151032;0.769427;,
  0.159912;0.798164;,
  0.183161;0.815925;,
  0.211899;0.815925;,
  0.235148;0.798164;,
  0.244028;0.769427;,
  0.211195;0.725205;,
  0.233307;0.742096;,
  0.183865;0.725205;,
  0.161753;0.742096;,
  0.153308;0.769427;,
  0.161753;0.796758;,
  0.183865;0.813649;,
  0.211195;0.813649;,
  0.233307;0.796758;,
  0.241752;0.769427;,
  0.209155;0.731809;,
  0.227963;0.746178;,
  0.185905;0.731809;,
  0.167097;0.746178;,
  0.159912;0.769427;,
  0.167097;0.792676;,
  0.185905;0.807045;,
  0.209155;0.807045;,
  0.227963;0.792676;,
  0.235148;0.769427;,
  0.205976;0.742096;,
  0.219641;0.752536;,
  0.189084;0.742096;,
  0.175419;0.752536;,
  0.170199;0.769427;,
  0.175419;0.786318;,
  0.189084;0.796758;,
  0.205976;0.796758;,
  0.219641;0.786318;,
  0.224861;0.769427;,
  0.201970;0.755058;,
  0.209155;0.760547;,
  0.193090;0.755058;,
  0.185905;0.760547;,
  0.183161;0.769427;,
  0.185905;0.778307;,
  0.193090;0.783796;,
  0.201970;0.783796;,
  0.209155;0.778307;,
  0.211899;0.769427;,
  0.197530;0.769427;,
  0.197530;0.769427;;
 }
}
