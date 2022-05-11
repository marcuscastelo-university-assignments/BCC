using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapGenerator : MonoBehaviour
{
    public uint mapWidth;
    public uint mapHeight;

    public uint octaves;

    [Range(0, 1)]
    public float persistance;
    public float lacunarity;

    public float noiseScale;

    public int seed;    
    public Vector2 offset;

    public bool autoUpdate;

    public void GenerateMap()
    {
        float[,] noiseMap = Noise.GenerateNoiseMap(mapWidth, mapHeight, seed, noiseScale, octaves, persistance, lacunarity, offset);

        MapDisplay mapDisplay = GetComponent<MapDisplay>();
        mapDisplay.DrawNoiseMap(noiseMap);
    }

    void OnValidate() {
        if (mapWidth < 1) mapWidth = 1;
        if (mapHeight < 1) mapHeight = 1;


        if (lacunarity < 1) lacunarity = 1;
        if (octaves < 0) octaves = 0;
        if (noiseScale < 0.1f) noiseScale = 0.1f;
    }
}
