@TerrainLayersTextures@

#define FE_TERRAIN_MAX_LAYERS 8
uniform float usedLayersCount;

struct materialPropertiesData
{
    float normalMapIntensity;
	float AOIntensity;
	float AOMapIntensity;
	float roughtness;
	float roughtnessMapIntensity;
	float metalness;
	float metalnessMapIntensity;
	float displacementMapIntensity;
	float tiling;
};

layout(std430, binding = 0) readonly buffer materialProperties
{
	materialPropertiesData materials[];
};

struct layerMaterialInfo
{
	vec4 albedo;
    vec3 normal;
	float AO;
	float roughtness;
	float metalness;
	float displacement;
};

layerMaterialInfo layerMaterial[FE_TERRAIN_MAX_LAYERS];

in GS_OUT
{
	vec2 UV;
	vec3 worldPosition;
	vec4 viewPosition;
	mat3 TBN;
	vec3 vertexNormal;
} FS_IN;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec3 gPosition;
layout (location = 2) out vec3 gNormal;
layout (location = 3) out vec4 gAlbedo;
layout (location = 4) out vec4 gMaterialProperties;
layout (location = 5) out vec4 gShaderProperties;

@Texture@ projectedMap;

@Texture@ heightMap;
uniform vec2 tileMult;
@Texture@ layerMap;
@Texture@ layerMap2;

void main(void)
{
	vec4 finalColor = vec4(0);
	vec3 finalNormal = vec3(0);
	vec4 finalMaterialProperties = vec4(0);

	gPosition = FS_IN.worldPosition;
	
	
	
	
	
	
	vec2 tiledUV = FS_IN.UV / materials[0].tiling;
	layerMaterial[0].albedo = texture(textures[0], tiledUV);
	
	layerMaterial[0].normal = texture(textures[1], tiledUV).xyz;
	layerMaterial[0].normal = normalize(layerMaterial[0].normal * 2.0 - 1.0);
	layerMaterial[0].normal = normalize(FS_IN.TBN * layerMaterial[0].normal);
	layerMaterial[0].normal = mix(FS_IN.vertexNormal, layerMaterial[0].normal, materials[0].normalMapIntensity);
	
	vec4 layerMaterialPropertiesTemp = texture(textures[2], tiledUV);
	layerMaterial[0].AO = layerMaterialPropertiesTemp.r * materials[0].AOMapIntensity;
	layerMaterial[0].AO = mix(materials[0].AOIntensity, layerMaterial[0].AO, materials[0].AOMapIntensity);
	layerMaterial[0].roughtness = layerMaterialPropertiesTemp.g * materials[0].roughtnessMapIntensity;
	layerMaterial[0].metalness = layerMaterialPropertiesTemp.b * materials[0].metalnessMapIntensity;
	layerMaterial[0].displacement = layerMaterialPropertiesTemp.a * materials[0].displacementMapIntensity;
	
	
	
	
	
	
	
	tiledUV = FS_IN.UV / materials[1].tiling;
	layerMaterial[1].albedo = texture(textures[3], tiledUV);
	
	layerMaterial[1].normal = texture(textures[4], tiledUV).xyz;
	layerMaterial[1].normal = normalize(layerMaterial[1].normal * 2.0 - 1.0);
	layerMaterial[1].normal = normalize(FS_IN.TBN * layerMaterial[1].normal);
	layerMaterial[1].normal = mix(FS_IN.vertexNormal, layerMaterial[1].normal, materials[1].normalMapIntensity);
	
	layerMaterialPropertiesTemp = texture(textures[5], tiledUV);
	layerMaterial[1].AO = layerMaterialPropertiesTemp.r * materials[1].AOMapIntensity;
	layerMaterial[1].AO = mix(materials[1].AOIntensity, layerMaterial[1].AO, materials[1].AOMapIntensity);
	layerMaterial[1].roughtness = layerMaterialPropertiesTemp.g * materials[1].roughtnessMapIntensity;
	layerMaterial[1].metalness = layerMaterialPropertiesTemp.b * materials[1].metalnessMapIntensity;
	layerMaterial[1].displacement = layerMaterialPropertiesTemp.a * materials[1].displacementMapIntensity;
	
	
	
	
	
	
	
	tiledUV = FS_IN.UV / materials[2].tiling;
	layerMaterial[2].albedo = texture(textures[6], tiledUV);
	
	layerMaterial[2].normal = texture(textures[7], tiledUV).xyz;
	layerMaterial[2].normal = normalize(layerMaterial[2].normal * 2.0 - 1.0);
	layerMaterial[2].normal = normalize(FS_IN.TBN * layerMaterial[2].normal);
	layerMaterial[2].normal = mix(FS_IN.vertexNormal, layerMaterial[2].normal, materials[2].normalMapIntensity);
	
	layerMaterialPropertiesTemp = texture(textures[8], tiledUV);
	layerMaterial[2].AO = layerMaterialPropertiesTemp.r * materials[2].AOMapIntensity;
	layerMaterial[2].AO = mix(materials[2].AOIntensity, layerMaterial[2].AO, materials[2].AOMapIntensity);
	layerMaterial[2].roughtness = layerMaterialPropertiesTemp.g * materials[2].roughtnessMapIntensity;
	layerMaterial[2].metalness = layerMaterialPropertiesTemp.b * materials[2].metalnessMapIntensity;
	layerMaterial[2].displacement = layerMaterialPropertiesTemp.a * materials[2].displacementMapIntensity;
	
	
	
	
	
	
	
	tiledUV = FS_IN.UV / materials[3].tiling;
	layerMaterial[3].albedo = texture(textures[9], tiledUV);
	
	layerMaterial[3].normal = texture(textures[10], tiledUV).xyz;
	layerMaterial[3].normal = normalize(layerMaterial[3].normal * 2.0 - 1.0);
	layerMaterial[3].normal = normalize(FS_IN.TBN * layerMaterial[3].normal);
	layerMaterial[3].normal = mix(FS_IN.vertexNormal, layerMaterial[3].normal, materials[3].normalMapIntensity);
	
	layerMaterialPropertiesTemp = texture(textures[11], tiledUV);
	layerMaterial[3].AO = layerMaterialPropertiesTemp.r * materials[3].AOMapIntensity;
	layerMaterial[3].AO = mix(materials[3].AOIntensity, layerMaterial[3].AO, materials[3].AOMapIntensity);
	layerMaterial[3].roughtness = layerMaterialPropertiesTemp.g * materials[3].roughtnessMapIntensity;
	layerMaterial[3].metalness = layerMaterialPropertiesTemp.b * materials[3].metalnessMapIntensity;
	layerMaterial[3].displacement = layerMaterialPropertiesTemp.a * materials[3].displacementMapIntensity;
	
	
	
	
	
	tiledUV = FS_IN.UV / materials[4].tiling;
	layerMaterial[4].albedo = texture(textures[12], tiledUV);
	
	layerMaterial[4].normal = texture(textures[13], tiledUV).xyz;
	layerMaterial[4].normal = normalize(layerMaterial[4].normal * 2.0 - 1.0);
	layerMaterial[4].normal = normalize(FS_IN.TBN * layerMaterial[4].normal);
	layerMaterial[4].normal = mix(FS_IN.vertexNormal, layerMaterial[4].normal, materials[4].normalMapIntensity);
	
	layerMaterialPropertiesTemp = texture(textures[14], tiledUV);
	layerMaterial[4].AO = layerMaterialPropertiesTemp.r * materials[4].AOMapIntensity;
	layerMaterial[4].AO = mix(materials[4].AOIntensity, layerMaterial[4].AO, materials[4].AOMapIntensity);
	layerMaterial[4].roughtness = layerMaterialPropertiesTemp.g * materials[4].roughtnessMapIntensity;
	layerMaterial[4].metalness = layerMaterialPropertiesTemp.b * materials[4].metalnessMapIntensity;
	layerMaterial[4].displacement = layerMaterialPropertiesTemp.a * materials[4].displacementMapIntensity;
	
	
	
	
	
	
	
	
	
	tiledUV = FS_IN.UV / materials[5].tiling;
	layerMaterial[5].albedo = texture(textures[15], tiledUV);
	
	layerMaterial[5].normal = texture(textures[16], tiledUV).xyz;
	layerMaterial[5].normal = normalize(layerMaterial[5].normal * 2.0 - 1.0);
	layerMaterial[5].normal = normalize(FS_IN.TBN * layerMaterial[5].normal);
	layerMaterial[5].normal = mix(FS_IN.vertexNormal, layerMaterial[5].normal, materials[5].normalMapIntensity);
	
	layerMaterialPropertiesTemp = texture(textures[17], tiledUV);
	layerMaterial[5].AO = layerMaterialPropertiesTemp.r * materials[5].AOMapIntensity;
	layerMaterial[5].AO = mix(materials[5].AOIntensity, layerMaterial[5].AO, materials[5].AOMapIntensity);
	layerMaterial[5].roughtness = layerMaterialPropertiesTemp.g * materials[5].roughtnessMapIntensity;
	layerMaterial[5].metalness = layerMaterialPropertiesTemp.b * materials[5].metalnessMapIntensity;
	layerMaterial[5].displacement = layerMaterialPropertiesTemp.a * materials[5].displacementMapIntensity;
	
	
	
	
	
	
	
	
	
	
	tiledUV = FS_IN.UV / materials[6].tiling;
	layerMaterial[6].albedo = texture(textures[18], tiledUV);
	
	layerMaterial[6].normal = texture(textures[19], tiledUV).xyz;
	layerMaterial[6].normal = normalize(layerMaterial[6].normal * 2.0 - 1.0);
	layerMaterial[6].normal = normalize(FS_IN.TBN * layerMaterial[6].normal);
	layerMaterial[6].normal = mix(FS_IN.vertexNormal, layerMaterial[6].normal, materials[6].normalMapIntensity);
	
	layerMaterialPropertiesTemp = texture(textures[20], tiledUV);
	layerMaterial[6].AO = layerMaterialPropertiesTemp.r * materials[6].AOMapIntensity;
	layerMaterial[6].AO = mix(materials[6].AOIntensity, layerMaterial[6].AO, materials[6].AOMapIntensity);
	layerMaterial[6].roughtness = layerMaterialPropertiesTemp.g * materials[6].roughtnessMapIntensity;
	layerMaterial[6].metalness = layerMaterialPropertiesTemp.b * materials[6].metalnessMapIntensity;
	layerMaterial[6].displacement = layerMaterialPropertiesTemp.a * materials[6].displacementMapIntensity;
	
	
	
	
	
	
	
	tiledUV = FS_IN.UV / materials[7].tiling;
	layerMaterial[7].albedo = texture(textures[21], tiledUV);
	
	layerMaterial[7].normal = texture(textures[22], tiledUV).xyz;
	layerMaterial[7].normal = normalize(layerMaterial[7].normal * 2.0 - 1.0);
	layerMaterial[7].normal = normalize(FS_IN.TBN * layerMaterial[7].normal);
	layerMaterial[7].normal = mix(FS_IN.vertexNormal, layerMaterial[7].normal, materials[7].normalMapIntensity);
	
	layerMaterialPropertiesTemp = texture(textures[23], tiledUV);
	layerMaterial[7].AO = layerMaterialPropertiesTemp.r * materials[7].AOMapIntensity;
	layerMaterial[7].AO = mix(materials[7].AOIntensity, layerMaterial[7].AO, materials[7].AOMapIntensity);
	layerMaterial[7].roughtness = layerMaterialPropertiesTemp.g * materials[7].roughtnessMapIntensity;
	layerMaterial[7].metalness = layerMaterialPropertiesTemp.b * materials[7].metalnessMapIntensity;
	layerMaterial[7].displacement = layerMaterialPropertiesTemp.a * materials[7].displacementMapIntensity;
	
	
	
	
	//for (int i = 0; i < usedLayersCount; i++)
	//{
	//	vec2 tiledUV = FS_IN.UV / materials[i].tiling;

	//	layerMaterial[i].albedo = texture(textures[i * 3], tiledUV);

	//	// ******************* normals *******************
	//	layerMaterial[i].normal = texture(textures[i * 3 + 1], tiledUV).xyz;
	//	layerMaterial[i].normal = normalize(layerMaterial[i].normal * 2.0 - 1.0);
	//	layerMaterial[i].normal = normalize(FS_IN.TBN * layerMaterial[i].normal);
	//	layerMaterial[i].normal = mix(FS_IN.vertexNormal, layerMaterial[i].normal, materials[i].normalMapIntensity);
	//	// ******************* normals END *******************

	//	// ******************* material properties *******************
	//	vec4 layerMaterialPropertiesTemp = texture(textures[i * 3 + 2], tiledUV);
	//	layerMaterial[i].AO = layerMaterialPropertiesTemp.r * materials[i].AOMapIntensity;
	//	layerMaterial[i].AO = mix(materials[i].AOIntensity, layerMaterial[i].AO, materials[i].AOMapIntensity);
	//	layerMaterial[i].roughtness = layerMaterialPropertiesTemp.g * materials[i].roughtnessMapIntensity;
	//	layerMaterial[i].metalness = layerMaterialPropertiesTemp.b * materials[i].metalnessMapIntensity;
	//	layerMaterial[i].displacement = layerMaterialPropertiesTemp.a * materials[i].displacementMapIntensity;
	//	// ******************* material properties END *******************
	//}
	
	vec4 firstLayersMap = texture(layerMap, FS_IN.UV / vec2(tileMult));
	vec4 secondLayersMap = texture(layerMap2, FS_IN.UV / vec2(tileMult));
	
	
	
	
	if (usedLayersCount > 0)
	{
		finalColor += layerMaterial[0].albedo * firstLayersMap[0];
		finalNormal += layerMaterial[0].normal * firstLayersMap[0];

		finalMaterialProperties.r += layerMaterial[0].AO * firstLayersMap[0];
		finalMaterialProperties.g += layerMaterial[0].roughtness * firstLayersMap[0];
		finalMaterialProperties.b += layerMaterial[0].metalness * firstLayersMap[0];
		finalMaterialProperties.a += layerMaterial[0].displacement * firstLayersMap[0];
	}
	
	
	
	if (usedLayersCount > 1)
	{
		finalColor += layerMaterial[1].albedo * firstLayersMap[1];
		finalNormal += layerMaterial[1].normal * firstLayersMap[1];

		finalMaterialProperties.r += layerMaterial[1].AO * firstLayersMap[1];
		finalMaterialProperties.g += layerMaterial[1].roughtness * firstLayersMap[1];
		finalMaterialProperties.b += layerMaterial[1].metalness * firstLayersMap[1];
		finalMaterialProperties.a += layerMaterial[1].displacement * firstLayersMap[1];
	}
	
	
	if (usedLayersCount > 2)
	{
		finalColor += layerMaterial[2].albedo * firstLayersMap[2];
		finalNormal += layerMaterial[2].normal * firstLayersMap[2];

		finalMaterialProperties.r += layerMaterial[2].AO * firstLayersMap[2];
		finalMaterialProperties.g += layerMaterial[2].roughtness * firstLayersMap[2];
		finalMaterialProperties.b += layerMaterial[2].metalness * firstLayersMap[2];
		finalMaterialProperties.a += layerMaterial[2].displacement * firstLayersMap[2];
	}
	
	
	
	if (usedLayersCount > 3)
	{
		finalColor += layerMaterial[3].albedo * firstLayersMap[3];
		finalNormal += layerMaterial[3].normal * firstLayersMap[3];

		finalMaterialProperties.r += layerMaterial[3].AO * firstLayersMap[3];
		finalMaterialProperties.g += layerMaterial[3].roughtness * firstLayersMap[3];
		finalMaterialProperties.b += layerMaterial[3].metalness * firstLayersMap[3];
		finalMaterialProperties.a += layerMaterial[3].displacement * firstLayersMap[3];
	}
	
	
	
	
	if (usedLayersCount > 4)
	{
		finalColor += layerMaterial[4].albedo * secondLayersMap[0];
		finalNormal += layerMaterial[4].normal * secondLayersMap[0];

		finalMaterialProperties.r += layerMaterial[4].AO * secondLayersMap[0];
		finalMaterialProperties.g += layerMaterial[4].roughtness * secondLayersMap[0];
		finalMaterialProperties.b += layerMaterial[4].metalness * secondLayersMap[0];
		finalMaterialProperties.a += layerMaterial[4].displacement * secondLayersMap[0];
	}
	
	
	
	
	if (usedLayersCount > 5)
	{
		finalColor += layerMaterial[5].albedo * secondLayersMap[1];
		finalNormal += layerMaterial[5].normal * secondLayersMap[1];

		finalMaterialProperties.r += layerMaterial[5].AO * secondLayersMap[1];
		finalMaterialProperties.g += layerMaterial[5].roughtness * secondLayersMap[1];
		finalMaterialProperties.b += layerMaterial[5].metalness * secondLayersMap[1];
		finalMaterialProperties.a += layerMaterial[5].displacement * secondLayersMap[1];
	}
	
	
	
	
	if (usedLayersCount > 6)
	{
		finalColor += layerMaterial[6].albedo * secondLayersMap[2];
		finalNormal += layerMaterial[6].normal * secondLayersMap[2];

		finalMaterialProperties.r += layerMaterial[6].AO * secondLayersMap[2];
		finalMaterialProperties.g += layerMaterial[6].roughtness * secondLayersMap[2];
		finalMaterialProperties.b += layerMaterial[6].metalness * secondLayersMap[2];
		finalMaterialProperties.a += layerMaterial[6].displacement * secondLayersMap[2];
	}
	
	
	
	if (usedLayersCount > 7)
	{
		finalColor += layerMaterial[7].albedo * secondLayersMap[3];
		finalNormal += layerMaterial[7].normal * secondLayersMap[3];

		finalMaterialProperties.r += layerMaterial[7].AO * secondLayersMap[3];
		finalMaterialProperties.g += layerMaterial[7].roughtness * secondLayersMap[3];
		finalMaterialProperties.b += layerMaterial[7].metalness * secondLayersMap[3];
		finalMaterialProperties.a += layerMaterial[7].displacement * secondLayersMap[3];
	}
	
	
	
	
	
	
	
	
	
	
	/*for (int i = 0; i < int(clamp(usedLayersCount, 0, 4)); i++)
	{
		finalColor += layerMaterial[i].albedo * firstLayersMap[i];
		finalNormal += layerMaterial[i].normal * firstLayersMap[i];

		finalMaterialProperties.r += layerMaterial[i].AO * firstLayersMap[i];
		finalMaterialProperties.g += layerMaterial[i].roughtness * firstLayersMap[i];
		finalMaterialProperties.b += layerMaterial[i].metalness * firstLayersMap[i];
		finalMaterialProperties.a += layerMaterial[i].displacement * firstLayersMap[i];
	}

	for (int i = 4; i < usedLayersCount; i++)
	{
		finalColor += layerMaterial[i].albedo * secondLayersMap[i - 4];
		finalNormal += layerMaterial[i].normal * secondLayersMap[i - 4];

		finalMaterialProperties.r += layerMaterial[i].AO * secondLayersMap[i - 4];
		finalMaterialProperties.g += layerMaterial[i].roughtness * secondLayersMap[i - 4];
		finalMaterialProperties.b += layerMaterial[i].metalness * secondLayersMap[i - 4];
		finalMaterialProperties.a += layerMaterial[i].displacement * secondLayersMap[i - 4];
	}*/
	
	gAlbedo = finalColor;
	gNormal = normalize(finalNormal);
	gMaterialProperties = finalMaterialProperties;
	
	gShaderProperties.r = 1; // 1 - shaderID
	gShaderProperties.g = texture(projectedMap, FS_IN.UV / tileMult).r;
	gShaderProperties.b = texture(projectedMap, FS_IN.UV / tileMult).g;
	gShaderProperties.a = texture(projectedMap, FS_IN.UV / tileMult).b;

	outColor = finalColor;
}
