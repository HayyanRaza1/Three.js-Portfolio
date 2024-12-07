import * as THREE from "three";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js"; // Correct import for OrbitControls

// Scene, Camera, Renderer setup
const scene = new THREE.Scene();
scene.background = new THREE.Color("#F0F0F0");
const camera = new THREE.PerspectiveCamera(
  75,
  window.innerWidth / window.innerHeight,
  0.1,
  1000
);
const renderer = new THREE.WebGLRenderer({
  canvas: document.getElementById("threeCanvas"),
});
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

// Create a dynamic camera control (OrbitControls)
const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true; // Smooth camera transitions
controls.dampingFactor = 0.25; // Optional: damping effect
controls.screenSpacePanning = false; // Optional: prevent panning outside the scene

// Lights (ambient, directional, and spotlights)
const ambientLight = new THREE.AmbientLight(0x404040, 0.5); // Soft light
scene.add(ambientLight);

const directionalLight = new THREE.DirectionalLight(0xffffff, 1);
directionalLight.position.set(5, 5, 5).normalize();
scene.add(directionalLight);

const spotLight = new THREE.SpotLight(0xffffff, 2);
spotLight.position.set(0, 5, 0);
spotLight.angle = Math.PI / 4;
spotLight.castShadow = true;
scene.add(spotLight);

// Create Platforms (using BoxGeometry)
function createPlatform(width, height, depth, position, color) {
  const geometry = new THREE.BoxGeometry(width, height, depth);
  const material = new THREE.MeshStandardMaterial({ color });
  const platform = new THREE.Mesh(geometry, material);
  platform.position.set(...position);
  platform.receiveShadow = true;
  scene.add(platform);
  return platform;
}

// Platforms
const platform1 = createPlatform(5, 0.5, 5, [0, -1, 0], 0x888888);
const platform2 = createPlatform(5, 0.5, 5, [10, -1, 10], 0x777777);
const platform3 = createPlatform(5, 0.5, 5, [-10, -1, -10], 0x666666);

// Create a rotating cube (moving object for interactivity)
const cubeGeometry = new THREE.BoxGeometry(1, 1, 1);
const cubeMaterial = new THREE.MeshLambertMaterial({ color: 0x00ff00 , emissive : 0x00ff00 });
const cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
cube.position.set(0, 1, 0);
cube.castShadow = true;
scene.add(cube);

// Camera setup
camera.position.z = 15;

// Animation loop
function animate() {
  requestAnimationFrame(animate);

  // Rotate the cube
  cube.rotation.x += 0.01;
  cube.rotation.y += 0.01;

  // Rotate the platforms
  platform1.rotation.y += 0.005;
  platform2.rotation.y += 0.005;
  platform3.rotation.y += 0.005;

  // Update the controls
  controls.update(); // Only required if controls.enableDamping is true

  // Render the scene
  renderer.render(scene, camera);
}

animate();

// Handle resizing of the window
window.addEventListener("resize", () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});
