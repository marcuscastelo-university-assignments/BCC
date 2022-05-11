using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Noise
{
    public static float[,] GenerateNoiseMap(uint width, uint height, int seed, float scale, uint octaves, float persistance, float lacunarity, Vector2 offset)
    {
        if (scale <= 0) scale = 0.01f;

        var prng = new System.Random(seed);
        Vector2[] octaveOffsets = new Vector2[octaves];
        for (int i = 0; i < octaves; i++)
        {
            octaveOffsets[i] = new Vector2(prng.Next(-100000, 100000) +offset.x, prng.Next(-100000, 100000) + offset.y);
        }

        float minNoise = float.MaxValue;
        float maxNoise = float.MinValue;

        float halfWidth = width / 2.0f;
        float halfHeight = height / 2.0f;

        float[,] noiseMap = new float[width, height];
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                float amplitude = 1;
                float frequency = 1;
                noiseMap[x, y] = 0;

                for (int i = 0; i < octaves; i++)
                {
                    float sampleX = ((x - halfWidth) / scale) * frequency + octaveOffsets[i].x;
                    float sampleY = ((y - halfHeight) / scale) * frequency + octaveOffsets[i].y;
                    noiseMap[x, y] += Mathf.PerlinNoise(sampleX * frequency, sampleY * frequency) * amplitude * 2 - 1;

                    amplitude *= persistance;
                    frequency *= lacunarity;
                }

                if (noiseMap[x, y] < minNoise) minNoise = noiseMap[x, y];
                if (noiseMap[x, y] > maxNoise) maxNoise = noiseMap[x, y];
            }
        }

        for (int x = 0; x < width; x++)
            for (int y = 0; y < height; y++)
                noiseMap[x, y] = Mathf.InverseLerp(minNoise, maxNoise, noiseMap[x, y]);

        return noiseMap;
     }
}
