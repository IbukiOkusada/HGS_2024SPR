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
 32;
 19.35966;0.53154;-6.92904;,
 19.35966;-8.32557;-6.92904;,
 18.02346;-8.32557;-8.48946;,
 18.02346;0.53154;-8.48946;,
 -18.89442;0.53154;-6.92904;,
 -15.53364;1.09461;-6.92904;,
 -15.53364;0.53154;-9.12351;,
 -18.10812;0.53154;-8.48946;,
 -18.89442;-8.32557;-6.92904;,
 -18.10812;-8.32557;-8.48946;,
 -15.53364;-10.52163;-6.92904;,
 -15.53364;-8.32557;-9.12351;,
 -18.10812;-8.32557;8.09817;,
 -15.53364;-8.32557;9.08760;,
 -15.53364;0.53154;9.08760;,
 -18.10812;0.53154;8.09817;,
 15.36591;1.09461;-6.92904;,
 15.36591;0.53154;-9.12351;,
 15.36594;-8.32557;-9.12351;,
 15.36594;-10.52163;-6.92904;,
 15.36594;-8.32557;9.08760;,
 15.36591;0.53154;9.08760;,
 18.02346;-8.32557;8.09817;,
 18.02346;0.53154;8.09817;,
 19.35966;-8.32557;6.25260;,
 15.36594;-10.52163;6.25260;,
 -15.53364;-10.52163;6.25260;,
 -18.89442;-8.32557;6.25260;,
 -18.89442;0.53154;6.25260;,
 -15.53364;1.09461;6.25260;,
 15.36591;1.09461;6.25260;,
 19.35966;0.53154;6.25260;;
 
 30;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,4,7,9;,
 4;10,8,9,11;,
 4;6,11,9,7;,
 4;12,13,14,15;,
 4;5,16,17,6;,
 4;17,18,11,6;,
 4;19,10,11,18;,
 4;14,13,20,21;,
 4;16,0,3,17;,
 4;2,18,17,3;,
 4;1,19,18,2;,
 4;21,20,22,23;,
 4;24,25,19,1;,
 4;25,26,10,19;,
 4;26,27,8,10;,
 4;27,28,4,8;,
 4;28,29,5,4;,
 4;29,30,16,5;,
 4;30,31,0,16;,
 4;31,24,1,0;,
 4;20,25,24,22;,
 4;13,26,25,20;,
 4;12,27,26,13;,
 4;15,28,27,12;,
 4;14,29,28,15;,
 4;21,30,29,14;,
 4;23,31,30,21;,
 4;22,24,31,23;;
 
 MeshMaterialList {
  1;
  30;
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
    "data\\TEXTURE\\UV\\player_UV.png";
   }
  }
 }
 MeshNormals {
  44;
  0.572350;-0.309292;0.759443;,
  0.492091;-0.291127;-0.820422;,
  0.605406;0.000000;0.795917;,
  0.521348;0.000000;-0.853345;,
  -0.694323;0.000000;0.719664;,
  -0.113425;0.979526;-0.166321;,
  -0.654505;-0.319702;0.685138;,
  -0.584675;-0.306327;-0.751212;,
  -0.182432;0.000000;0.983219;,
  -0.056853;0.976488;-0.207942;,
  -0.169391;-0.418348;-0.892352;,
  -0.217144;-0.464521;0.858527;,
  0.177264;0.000000;0.984163;,
  0.049686;0.974991;-0.216618;,
  0.151679;-0.411202;-0.898836;,
  0.198667;-0.459409;0.865722;,
  0.781331;-0.504107;-0.367964;,
  0.216631;-0.913922;-0.343247;,
  -0.249305;-0.910187;-0.330765;,
  -0.830619;-0.480169;-0.281975;,
  -0.139864;0.986646;-0.083478;,
  -0.070263;0.992029;-0.104603;,
  0.060188;0.992218;-0.109000;,
  0.937968;0.000000;-0.346721;,
  0.426274;-0.871347;0.242991;,
  0.221089;-0.931161;0.289930;,
  -0.252719;-0.926503;0.278793;,
  -0.840432;-0.485970;0.239807;,
  -0.979792;0.000000;0.200020;,
  -0.071787;0.994012;0.082381;,
  0.061708;0.994372;0.086121;,
  0.123055;0.989633;0.074051;,
  -0.972890;0.000000;-0.231270;,
  -0.623142;0.000000;-0.782109;,
  -0.120445;0.000000;-0.992720;,
  0.116836;0.000000;-0.993151;,
  0.119937;0.988474;-0.092381;,
  0.099196;0.977920;-0.183937;,
  -0.143020;0.987484;0.066481;,
  0.951313;0.000000;0.308226;,
  -0.060187;0.984606;0.164098;,
  -0.120099;0.983862;0.132636;,
  0.052986;0.983753;0.171530;,
  0.105795;0.983361;0.147676;;
  30;
  4;23,16,1,3;,
  4;20,21,9,5;,
  4;19,32,33,7;,
  4;18,19,7,10;,
  4;34,10,7,33;,
  4;6,11,8,4;,
  4;21,22,13,9;,
  4;35,14,10,34;,
  4;17,18,10,14;,
  4;8,11,15,12;,
  4;22,36,37,13;,
  4;1,14,35,3;,
  4;16,17,14,1;,
  4;12,15,0,2;,
  4;24,25,17,16;,
  4;25,26,18,17;,
  4;26,27,19,18;,
  4;27,28,32,19;,
  4;38,29,21,20;,
  4;29,30,22,21;,
  4;30,31,36,22;,
  4;39,39,16,23;,
  4;15,25,24,0;,
  4;11,26,25,15;,
  4;6,27,26,11;,
  4;4,28,27,6;,
  4;40,29,38,41;,
  4;42,30,29,40;,
  4;43,31,30,42;,
  4;0,39,39,2;;
 }
 MeshTextureCoords {
  32;
  0.784414;0.536614;,
  0.784414;0.656390;,
  0.789901;0.656390;,
  0.789901;0.536614;,
  0.941503;0.536614;,
  0.927702;0.528999;,
  0.927702;0.536614;,
  0.938274;0.536614;,
  0.941503;0.656390;,
  0.938274;0.656390;,
  0.927702;0.686087;,
  0.927702;0.656390;,
  0.938274;0.656390;,
  0.927702;0.656390;,
  0.927702;0.536614;,
  0.938274;0.536614;,
  0.800814;0.528999;,
  0.800814;0.536614;,
  0.800814;0.656390;,
  0.800814;0.686087;,
  0.800814;0.656390;,
  0.800814;0.536614;,
  0.789901;0.656390;,
  0.789901;0.536614;,
  0.784414;0.656390;,
  0.800814;0.686087;,
  0.927702;0.686087;,
  0.941503;0.656390;,
  0.941503;0.536614;,
  0.927702;0.528999;,
  0.800814;0.528999;,
  0.784414;0.536614;;
 }
}
