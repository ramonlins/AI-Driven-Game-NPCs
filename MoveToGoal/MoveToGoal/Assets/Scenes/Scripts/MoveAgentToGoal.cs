using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.MLAgents;
using Unity.MLAgents.Actuators;
using Unity.MLAgents.Sensors;
using Unity.VisualScripting;

public class MoveAgentToGoal : Agent
{

    [SerializeField] private Transform targetTransform;
    [SerializeField] private Material winMaterial;
    [SerializeField] private Material loseMaterial;
    [SerializeField] private MeshRenderer floorMeshRenderer;

    // Restart episode
    public override void OnEpisodeBegin()
    {
        transform.localPosition = new Vector3(Random.Range(-7f, 9f), 1f, Random.Range(-3f, 4f));
        targetTransform.localPosition = new Vector3(Random.Range(-8f, 9f), 1f, Random.Range(-3f, 4f));


    }

    // Define what will be observed by the agent
    public override void CollectObservations(VectorSensor sensor)
    {
        // Get self position
        sensor.AddObservation(transform.localPosition);

        // Get target position
        sensor.AddObservation(targetTransform.localPosition);
    }

    // Create the behavior of the agent
    public override void OnActionReceived(ActionBuffers actions)
    {
        float moveX = actions.ContinuousActions[0];
        float moveZ = actions.ContinuousActions[1];

        float agentSpeed = 4f;
        transform.localPosition += new Vector3(moveX, 0, moveZ) * Time.deltaTime * agentSpeed;
    }

    // Create heuristic controlling
    public override void Heuristic(in ActionBuffers actionsOut)
    {
        ActionSegment<float> continuousAction = actionsOut.ContinuousActions;
        continuousAction[0] = Input.GetAxisRaw("Horizontal");
        continuousAction[1] = Input.GetAxisRaw("Vertical");
    }

    // Check if collider has a specific component, if true, pass as reference
    private void OnTriggerEnter(Collider other){
        if (other.TryGetComponent<Goal>(out Goal goal)){
            SetReward(1f);
            floorMeshRenderer.material = winMaterial;  // Green when hit goal
            EndEpisode();
        }
        // Check if has a wall component
        if (other.TryGetComponent<Wall>(out Wall wall)){
            SetReward(-1f);
            floorMeshRenderer.material = loseMaterial;  // Red when hit walls
            EndEpisode();
        }

    }
}
