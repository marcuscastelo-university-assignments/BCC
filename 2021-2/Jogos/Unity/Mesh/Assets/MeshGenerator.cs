using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(MeshFilter))]
public class MeshGenerator : MonoBehaviour
{
    Mesh mesh;

    Vector3[] vertices;
    int[] triangles;

    public int xSize = 20;
    public int zSize = 20;

    delegate float Elevate(float x, float z);

    // Start is called before the first frame update
    void Start()
    {
        mesh = CreateShape((x,z) => Mathf.PerlinNoise(x * .3f, z * .3f) * 2f);

        MeshFilter meshFilter = GetComponent<MeshFilter>();
        meshFilter.mesh = mesh;
    }

    Mesh CreateShape(Elevate elevate)
    {
        Mesh mesh = new Mesh();

        FillVertices(elevate);
        FillTriangles();

        mesh.Clear();
        mesh.vertices = vertices;
        mesh.triangles = triangles;
        mesh.RecalculateNormals();

        return mesh;
    }

    void FillVertices(Elevate elevate = null)
    {
        elevate = elevate ?? ((x,z)=>x);
        vertices = new Vector3[(xSize + 1) * (zSize + 1)];

        for (int z = 0; z <= zSize; z++)
            for (int x = 0; x <= xSize; x++)
                vertices[z * (xSize + 1) + x] = new Vector3(x, elevate(x, z), z);
    }

    void FillTriangles()
    {
        int squareCount = xSize * zSize;
        int triangleCount = squareCount * 2;
        int indicesCount = triangleCount * 3;
        triangles = new int[indicesCount];

        int i = 0;
        for (int z = 0; z < zSize; z++)
        {
            for (int x = 0; x < xSize; x++)
            {
                int bl = z  * (xSize + 1) + x;
                int tl = bl + (xSize + 1);
                int tr = tl + 1;
                int br = bl + 1;

                triangles[i++] = bl;
                triangles[i++] = tl;
                triangles[i++] = tr;

                triangles[i++] = tr;
                triangles[i++] = br;
                triangles[i++] = bl;
            }
        }

    }

    // private void OnGizmosS

    private void OnDrawGizmos()
    {
        
        // FillVertices();

        // Gizmos.DrawLine(new Vector3(0, 0, 0), new Vector3(xSize, 0, 0));
        // Gizmos.DrawLine(new Vector3(0, 0, 0), new Vector3(0, 0, zSize));
        // Gizmos.DrawMesh(CreateShape(), transform.position, transform.rotation);

        // foreach (var item in vertices)
        // {
        //     Gizmos.DrawSphere(item, .1f);
        // }
    }
}
