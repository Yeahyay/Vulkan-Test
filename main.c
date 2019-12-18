#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <locale.h>
// #include <stddef.h>
#include <ctype.h>

#include <Core/vector.h>
#include <Core/set.h>

#include <gsl/gsl_vector.h>

#define error(...)	\
	printf("YEET\n");	\
	fprintf(stderr, __VA_ARGS__);	\
	exit(EXIT_FAILURE)

#define INFO_DEBUG
#define INFO_IMPORTANCE_MIN 0
#define INFO_IMPORTANCE_MAX 100

#ifdef INFO_DEBUG
	#define info(value, ...)	\
		if (INFO_IMPORTANCE_MIN <= value && value <= INFO_IMPORTANCE_MAX) {	\
			printf(__VA_ARGS__);	\
		}
#else
	#define info(value, ...)
#endif

const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_FRAMES_IN_FLIGHT = 2;

// TYPE DEFINITIONS

typedef struct {
	double x;
	double y;
} vec2;
vec2 vec2_init = {
	0, 0
};
typedef struct {
	double x;
	double y;
	double z;
} vec3;
vec3 vec3_init = {
	0, 0, 0
};

typedef struct {
	vec2 pos;
	vec3 color;
	void (*getBindingDescription)(VkVertexInputBindingDescription*);
} Vertex;
void Vertex_getBindingDescription(VkVertexInputBindingDescription* bindingDescription) {
 	// *bindingDescription = {0};
	bindingDescription->binding = 0;
	bindingDescription->stride = sizeof(Vertex);
	bindingDescription->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
 	// return bindingDescription;
}
void Vertex_getAttributeDescriptions(VkVertexInputAttributeDescription attributeDescriptions[2]) {
	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attributeDescriptions[0].offset = offsetof(Vertex, pos);

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = offsetof(Vertex, color);
}
Vertex Vertex_init = {
	{0, 0},
	{0, 0, 0},
	&Vertex_getBindingDescription
};

// DYNAMIC DATA TYPE GENRATIONS
// VECTORS
generate_vector(const char*, constCharP);

generate_vector(VkPhysicalDevice, VkPhysicalDevice);
generate_vector(VkDeviceQueueCreateInfo, VkDeviceQueueCreateInfo);
generate_vector(VkExtensionProperties, VkExtensionProperties);
generate_vector(VkQueueFamilyProperties, VkQueueFamilyProperties);

generate_vector(VkSurfaceFormatKHR, VkSurfaceFormatKHR);
generate_vector(VkPresentModeKHR, VkPresentModeKHR);
generate_vector(VkImage, VkImage);
generate_vector(VkImageView, VkImageView);

generate_vector(char, char);
generate_vector(uint32_t, uint32);

generate_vector(VkFramebuffer, VkFramebuffer);
generate_vector(VkCommandBuffer, VkCommandBuffer);
generate_vector(VkSemaphore, VkSemaphore);
generate_vector(VkFence, VkFence);

generate_vector(VkVertexInputAttributeDescription, VkVertexInputAttributeDescription);
generate_vector(Vertex, Vertex);

// SETS
generate_set(char*, string,
	return a-b;
);
generate_set(uint32_t, uint32,
	return a-b;
);

// DYNAMIC DATA TYPE STATIC DECLARATIONS
vector_static(const char*, constCharP, validationLayers, 1,
	"VK_LAYER_KHRONOS_validation",
);
vector_static(const char*, constCharP, deviceExtensions, 1,
	VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	"Stinky",
	"COCK"
);

// #define NDEBUG

// PREPROCESSOR
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

// VECTOR RELIANT TYPE DEFINITIONS
typedef struct _QueueFamilyIndices QueueFamilyIndices;
struct _QueueFamilyIndices {
	uint32_t graphicsFamily;
	uint32_t presentFamily;
	bool (*isComplete)(QueueFamilyIndices* self);
};
bool isComplete(QueueFamilyIndices* self) {
	bool isGraphicsFamily = (self->graphicsFamily >= 0) ? true : false;
	bool isPresentFamily = (self->presentFamily >= 0) ? true : false;
	return isGraphicsFamily && isPresentFamily ? true : false ; // check if it has a value
}
QueueFamilyIndices QueueFamilyIndices_INIT = {
	-1, -1, &isComplete
};

typedef struct {
	VkSurfaceCapabilitiesKHR capabilities;
	VkSurfaceFormatKHR_vector* formats;
	VkPresentModeKHR_vector* presentModes;
} SwapChainSupportDetails;
SwapChainSupportDetails SwapChainSupportDetails_INIT = {
	{0},
	&(VkSurfaceFormatKHR_vector) vector_init(VkSurfaceFormatKHR, VkSurfaceFormatKHR, 1, 0, NULL),
	&(VkPresentModeKHR_vector) vector_init(VkPresentModeKHR, VkPresentModeKHR, 1, 0, NULL)
};

// DEBUG HANDLE CREATION AND DESTRUCTION
VkResult CreateDebugUtilsMessengerEXT(
	VkInstance instance,	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(
	VkInstance instance,	VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

// MAIN PROGRAM
void run(void);
void initWindow(void);
void framebufferResizeCallback(GLFWwindow* window, int width, int height);
void initVulkan(void);
void mainLoop(void);
void cleanupSwapChain(void);
void cleanup(void);

// CREATE VULKAN INSTANCE
void createInstance(void);

// SETUP DEBUG
void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo);
void setupDebugMessenger(void);

// CREATE VULKAN SURFACE
void createSurface(void);

// VULKAN DEVICES
void pickPhysicalDevice(void);
void createLogicalDevice(void);

// CREATE SWAPCHAIN
void createSwapChain(void);

// IMAGE VIEWS
void createImageViews(void);

// GRAPHICS PIPELINE
void createRenderPass(void);
void createGraphicsPipeline(void);
void createFramebuffers(void);
void createCommandPool(void);
void createCommandBuffers(void);
void createSyncObjects(void);
void drawFrame(void);
VkShaderModule createShaderModule(char_vector* code);

// SWAPCHAIN HELPER FUNCTIONS
VkSurfaceFormatKHR chooseSwapSurfaceFormat(VkSurfaceFormatKHR_vector* availableFormats);
VkPresentModeKHR chooseSwapPresentMode(const VkPresentModeKHR_vector* availablePresentModes);
VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities);
SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

// CHECK DEVICE SUITABILITY
bool isDeviceSuitable(VkPhysicalDevice device);

// HELPER FUNCTIONS
bool checkDeviceExtensionSupport(VkPhysicalDevice device);
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
constCharP_vector* getRequiredExtensions(void);
bool checkValidationLayerSupport(void);
char_vector* readFile(const char* filename);

// DEBUG CALLBACK
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

// FUNCTION DEFINITIONS

// creates the debug messenger object
VkResult CreateDebugUtilsMessengerEXT(
	VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	// gets the function pointer to create the debug messenger object
	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != NULL) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}	// END CreateDebugUtilsMessengerEXT

void DestroyDebugUtilsMessengerEXT(
	VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
	const VkAllocationCallbacks* pAllocator) {
	PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != NULL) {
		func(instance, debugMessenger, pAllocator);
	}
}	// END DestroyDebugUtilsMessengerEXT

void run(void) {
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}	// END run

GLFWwindow* window;

VkInstance instance; // handle for new instance
VkDebugUtilsMessengerEXT debugMessenger; // handle for debug callback
VkSurfaceKHR surface;

VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
VkDevice device;

VkQueue graphicsQueue;
VkQueue presentQueue;

VkSwapchainKHR swapChain;
vector_static_null(VkImage, VkImage, swapChainImages);
VkFormat swapChainImageFormat;
VkExtent2D swapChainExtent;
vector_static_null(VkImageView, VkImageView, swapChainImageViews);

VkRenderPass renderPass;
VkPipelineLayout pipelineLayout;
VkPipeline graphicsPipeline;

vector_static_null(VkFramebuffer, VkFramebuffer, swapChainFramebuffers);

VkCommandPool commandPool;
vector_static_null(VkCommandBuffer, VkCommandBuffer, commandBuffers);

vector_static_null(VkSemaphore, VkSemaphore, imageAvailableSemaphores);
vector_static_null(VkSemaphore, VkSemaphore, renderFinishedSemaphores);
vector_static_null(VkFence, VkFence, inFlightFences);
vector_static_null(VkFence, VkFence, imagesInFlight);
long long int currentFrame = 0;

bool framebufferResized = false;

VkBuffer vertexBuffer;
VkDeviceMemory vertexBufferMemory;

vector_static(Vertex, Vertex, vertices, 3,
	{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}, &Vertex_getBindingDescription},
	{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, &Vertex_getBindingDescription},
	{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, &Vertex_getBindingDescription},
);

void initWindow(void) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(WIDTH,HEIGHT, "Vulkan", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}	// END initWindow

void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	printf("resized %d %d\n", width, height);
	framebufferResized = true;
}	// END framebufferResizeCallback

void createVertexBuffer(void);

void initVulkan(void) {
	createInstance();
	setupDebugMessenger();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();

	// SWAP CHAIN
	createSwapChain();
	createImageViews();
	createRenderPass();
	createGraphicsPipeline();
	createFramebuffers();
	createCommandPool();
	// INDEPENDENT OF SWAP CHAIN
		createVertexBuffer();
	createCommandBuffers();

	createSyncObjects();
}	// END initVulkan

uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		// iterate through bitfields and check if the bit is the same with the type
		if (typeFilter & (1 << i) &&
			// also check  for desired special features
			(memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	error("failed to find suitable memory type!");
}

void createVertexBuffer(void) {
	VkBufferCreateInfo bufferInfo = {0};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = sizeof(vertices.data[0]) * vertices.size;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(device, &bufferInfo, NULL, &vertexBuffer) != VK_SUCCESS) {
		error("failed to create vertex buffer!");
	}

	VkMemoryRequirements memRequirements = {0};
	vkGetBufferMemoryRequirements(device, vertexBuffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {0};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(
		memRequirements.memoryTypeBits,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	if (vkAllocateMemory(device, &allocInfo, NULL, &vertexBufferMemory) != VK_SUCCESS) {
		error("failed to allocate vertex buffer memory!");
	}

	vkBindBufferMemory(device, vertexBuffer, vertexBufferMemory, 0);

	void* data;
	vkMapMemory(device, vertexBufferMemory, 0, bufferInfo.size, 0, &data);
	// copy data to mapped memory
	memcpy(data, vertices.data, bufferInfo.size);
	vkUnmapMemory(device, vertexBufferMemory);
}	// END createVertexBuffer

void recreateSwapChain() {
	int width = 0, height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(device);

	cleanupSwapChain();

	info(50, "\nRECREATING SWAPCHAIN\n\n");

	createSwapChain();
	createImageViews();
	createRenderPass();
	createGraphicsPipeline();
	createFramebuffers();
	createCommandBuffers();
}	// END recreateSwapChain

void mainLoop(void) {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		drawFrame();
	}
	vkDeviceWaitIdle(device);
}	// END mainLoop

void cleanupSwapChain() {
	for (int i = 0; i < swapChainFramebuffers.size; i++) {
		VkFramebuffer framebuffer = swapChainFramebuffers.data[i];
		vkDestroyFramebuffer(device, framebuffer, NULL);
		swapChainFramebuffers.data[i] = NULL;
	}
	// swapChainFramebuffers.size = 0;

	vkFreeCommandBuffers(device, commandPool, commandBuffers.size, commandBuffers.data);

	vkDestroyPipeline(device, graphicsPipeline, NULL);
	vkDestroyPipelineLayout(device, pipelineLayout, NULL);
	vkDestroyRenderPass(device, renderPass, NULL);

	for (int i = 0; i < swapChainImageViews.size; i++) {
		VkImageView imageView = swapChainImageViews.data[i];
		vkDestroyImageView(device, imageView, NULL);
		swapChainImageViews.data[i] = NULL;
	}
	// swapChainImageViews.size = 0;

	vkDestroySwapchainKHR(device, swapChain, NULL);
}	// END cleanupSwapChain

void cleanup(void) {
	cleanupSwapChain();

	vkDestroyBuffer(device, vertexBuffer, NULL);
	vkFreeMemory(device, vertexBufferMemory, NULL);

	for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(device, renderFinishedSemaphores.data[i], NULL);
		vkDestroySemaphore(device, imageAvailableSemaphores.data[i], NULL);
		vkDestroyFence(device, inFlightFences.data[i], NULL);
		renderFinishedSemaphores.data[i] = 0;
		imageAvailableSemaphores.data[i] = 0;
		inFlightFences.data[i] = 0;
	}
	// renderFinishedSemaphores.free(&renderFinishedSemaphores);

	vkDestroyCommandPool(device, commandPool, NULL);

	vkDestroyDevice(device, NULL);

	if (enableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(instance, debugMessenger, NULL);
	}

	vkDestroySurfaceKHR(instance, surface, NULL);
	vkDestroyInstance(instance, NULL);

	glfwDestroyWindow(window);

	glfwTerminate();
}	// END cleanup

void createInstance(void) {
	if (enableValidationLayers && !checkValidationLayerSupport()) {
		error("validation layers requested, but not available!");
	}
	// 1. Pointer to struct with creation info
	// 2. Pointer to custom allocator callbacks, always NULL for now
	// 3. Pointer to the variable that stores the handle to the new object

	// optional application information
	VkApplicationInfo appInfo = {0};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Yeahyay's Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_1;

	// specify global extensions and validation layers to use
	VkInstanceCreateInfo createInfo = {0};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;	// define structure type
	createInfo.pApplicationInfo = &appInfo;							// pass in application information struct

	constCharP_vector* extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = extensions->size;
	createInfo.ppEnabledExtensionNames = extensions->data;

	// determine amount of global validation layers to enable
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
	if (enableValidationLayers) {
		info(3, "VALIDATION LAYERS ENABLED\n");
		createInfo.enabledLayerCount = validationLayers.size;
		createInfo.ppEnabledLayerNames = validationLayers.data;

		populateDebugMessengerCreateInfo(&debugCreateInfo);
		createInfo.pNext = &debugCreateInfo;
	} else {
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = NULL;
	}

	// create the instance
	if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
		error("Failed to create instance\n");
	}

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);

	VkExtensionProperties instaceExtensions[extensionCount];

	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, instaceExtensions);

	info(3, "available extensions (%d):\n", extensionCount);
	for (int extension = 0; extension < extensionCount; extension++) {
		info(3, "\t%s\n", instaceExtensions[extension].extensionName);
	}
}	// END createInstance

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo) {
	createInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		// VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo->pfnUserCallback = debugCallback;
}	// END populateDebugMessengerCreateInfo

void setupDebugMessenger(void) {
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo = {0};
	populateDebugMessengerCreateInfo(&createInfo);

	if (CreateDebugUtilsMessengerEXT(instance, &createInfo, NULL, &debugMessenger) != VK_SUCCESS) {
		error("failed to set up debug messenger!\n");
	}
}	// END setupDebugMessenger

void createSurface(void) {
	if (glfwCreateWindowSurface(instance, window, NULL, &surface) != VK_SUCCESS) {
		error("failed to create window surface!");
	}
}	// END createSurface

void pickPhysicalDevice(void) {
	// query the number of graphics cards
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

	if (deviceCount == 0) {
		error("failed to find GPUs with Vulkan support!");
	}

	// store the physical devices
	VkPhysicalDevice_vector* devices = VkPhysicalDevice_vector_new(2, deviceCount);
	VkPhysicalDevice deviceArray[deviceCount];
	vkEnumeratePhysicalDevices(instance, &deviceCount, deviceArray);
	for (int i = 0; i < deviceCount; i++) {
		devices->append(devices, deviceArray[i]);
	}

	for (int i = 0; i < devices->size; i++) {
		VkPhysicalDevice device = devices->data[i];

		VkPhysicalDeviceProperties deviceProperties = {0};
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		info(3, "FOUND PHYSICAL DEVICE: %s\n", deviceProperties.deviceName);

		if (isDeviceSuitable(device)) {
			info(3, "DEVICE IS SUITABLE\n");
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		error("failed to find a suitable GPU!");
	}
	// free(devices);
}	// END pickPhysicalDevice

void createLogicalDevice(void) {
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	VkDeviceQueueCreateInfo_vector* queueCreateInfos = VkDeviceQueueCreateInfo_vector_new(2, 1);
	uint32_set* uniqueQueueFamilies = uint32_set_new(2, 2);
	uniqueQueueFamilies->append(uniqueQueueFamilies, indices.graphicsFamily);
	uniqueQueueFamilies->append(uniqueQueueFamilies, indices.presentFamily);

	float queuePriority = 1.0;
	for (int i = 0; i < uniqueQueueFamilies->size; i++) {
		uint32_t queueFamily = uniqueQueueFamilies->data[i];
		VkDeviceQueueCreateInfo queueCreateInfo = {0};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos->append(queueCreateInfos, queueCreateInfo);
	}
	// queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	// queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
	// queueCreateInfo.queueCount = 1;
	// queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures = {0};

	VkDeviceCreateInfo createInfo = {0};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos->data;
	createInfo.queueCreateInfoCount = queueCreateInfos->size;

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = deviceExtensions.size;
	createInfo.ppEnabledExtensionNames = deviceExtensions.data;
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = (uint32_t) validationLayers.size;
		createInfo.ppEnabledLayerNames = validationLayers.data;
	} else {
			createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createInfo, NULL, &device) != VK_SUCCESS) {
		error("failed to create logical device!");
	}

	// free(queueCreateInfos);
	// free(uniqueQueueFamilies);

	vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
	vkGetDeviceQueue(device, indices.presentFamily, 0, &presentQueue);
}	// END createLogicalDevice

void createSwapChain(void) {
	printf("creating swapchain\n");
	SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(&swapChainSupport.capabilities);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	uint32_t maxImageCount = swapChainSupport.capabilities.maxImageCount;
	if (maxImageCount > 0 && imageCount > maxImageCount) {
		imageCount = maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = {0};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;

	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	uint32_t queueFamilyIndices[] = {indices.graphicsFamily, indices.presentFamily};

	if (indices.graphicsFamily != indices.presentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	} else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = NULL; // Optional
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	// blend with other windows
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	// ignore window beinng obscured
	createInfo.clipped = VK_TRUE;

	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(device, &createInfo, NULL, &swapChain) != VK_SUCCESS) {
		error("failed to create swap chain!");
	}

	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, NULL);
	swapChainImages.resize(&swapChainImages, imageCount);
	swapChainImages.size = 0;

	VkImage swapChainImageData[imageCount];
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImageData);
	for (int i = 0; i < imageCount; i++) {
		swapChainImages.data[i] = swapChainImageData[i];
		// swapChainImages.append(&swapChainImages, swapChainImageData[i]);
	}
	swapChainImages.size = imageCount;
	// printf("SWAPCHAIN IMAGES SIZE: %I64d\n", swapChainImages.size);

	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;

	printf("created swapchain\n");
}	// END createSwapChain

void createImageViews(void) {
	// info(2, "%ld, %ld\n", (long unsigned int) swapChainImageViews.size, (long unsigned int) swapChainImageViews.threshold);
	swapChainImageViews.resize(&swapChainImageViews, swapChainImages.size);
	swapChainImageViews.size = 0;
	// info(2, "%ld, %ld\n", (long unsigned int) swapChainImageViews.size, (long unsigned int) swapChainImageViews.threshold);

	for (size_t i = 0; i < swapChainImages.size; i++) {
		VkImageViewCreateInfo createInfo = {0};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapChainImages.data[i];

		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapChainImageFormat;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		VkImageView newImageView;
		if (vkCreateImageView(device, &createInfo, NULL, &newImageView) != VK_SUCCESS) {
			error("failed to create image views!");
		}
		swapChainImageViews.append(&swapChainImageViews, newImageView);

		info(3, "CREATED IMAGE VIEW\n");
	}
}	// END createImageViews

void createRenderPass(void) {
	VkAttachmentDescription colorAttachment = {0};
	colorAttachment.format = swapChainImageFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {0};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {0};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkRenderPassCreateInfo renderPassInfo = {0};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	if (vkCreateRenderPass(device, &renderPassInfo, NULL, &renderPass) != VK_SUCCESS) {
		error("failed to create render pass!");
	}

	// dependencies specify what the subpass needs before executing
	VkSubpassDependency dependency = {0};
	// source of dependency
	// VK_SUBPASS_EXTERNAL refers to the implicit subpass before or after depending
	// on whether it is used in srcSubpass or dstSubpass
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	// dependent
	dependency.dstSubpass = 0;

	// specifies the operations to wait on
	// wait for the color attachment to output

	// dependency is the color attachment of source
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;

	// operations that need to wait for the source
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	// reading and writing are restricted
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	info(3, "CREATED RENDER PASS\n");
}	// END createRenderPass

void createGraphicsPipeline(void) {
	char_vector* vertShaderCode = readFile("Shaders/triangle_vert.spv");
	char_vector* fragShaderCode = readFile("Shaders/triangle_frag.spv");

	VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
	VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {0};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {0};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {0};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.vertexAttributeDescriptionCount = 0;

	VkVertexInputBindingDescription bindingDescription = {0};
	Vertex_getBindingDescription(&bindingDescription);
	VkVertexInputAttributeDescription attributeDescriptions[2] = {{0},{0}};
	Vertex_getAttributeDescriptions(attributeDescriptions);

	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount  = 2;
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions;

	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {0};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport = {0};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float) swapChainExtent.width;
	viewport.height = (float) swapChainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {0};
	scissor.offset = (VkOffset2D){0, 0};
	scissor.extent = swapChainExtent;

	VkPipelineViewportStateCreateInfo viewportState = {0};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer = {0};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling = {0};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineColorBlendAttachmentState colorBlendAttachment = {0};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo colorBlending = {0};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {0};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pushConstantRangeCount = 0;

	if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, NULL, &pipelineLayout) != VK_SUCCESS) {
		error("failed to create pipeline layout!");
	}

	VkGraphicsPipelineCreateInfo pipelineInfo = {0};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, NULL, &graphicsPipeline) != VK_SUCCESS) {
		error("failed to create graphics pipeline!");
	}
	info(3, "CREATED GRAPHICS PIPELINE\n");

	vkDestroyShaderModule(device, fragShaderModule, NULL);
	vkDestroyShaderModule(device, vertShaderModule, NULL);
}	// END createGraphicsPipeline

void createFramebuffers(void) {
	swapChainFramebuffers.resize(&swapChainFramebuffers, swapChainImageViews.size);
	swapChainFramebuffers.size = 0;
	// iterate through image views and create framebuffers
	for (size_t i = 0; i < swapChainImageViews.size; i++) {
		VkImageView attachments[] = {
			swapChainImageViews.data[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {0};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapChainExtent.width;
		framebufferInfo.height = swapChainExtent.height;
		framebufferInfo.layers = 1;

		VkFramebuffer swapChainFramebufferData = {0};
		if (vkCreateFramebuffer(device, &framebufferInfo, NULL, &swapChainFramebufferData) != VK_SUCCESS) {
			error("failed to create framebuffer!");
		}
		swapChainFramebuffers.append(&swapChainFramebuffers, swapChainFramebufferData);
		info(3, "\tCREATED FRAME BUFFER %d\n", (int) i);
	}
	info(3, "CREATED FRAME BUFFERS\n");
}	// END createFramebuffers

void createCommandPool(void) {
	QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

	VkCommandPoolCreateInfo poolInfo = {0};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
	// poolInfo.flags = 0; // Optional

	if (vkCreateCommandPool(device, &poolInfo, NULL, &commandPool) != VK_SUCCESS) {
		error("failed to create command pool!");
	}

	info(3, "CREATED COMMAND POOL\n");
}	// END createCommandPool

void createCommandBuffers(void) {
	commandBuffers.resize(&commandBuffers, swapChainFramebuffers.size);
	commandBuffers.size = 0;
	uint32_t commandBufferCount = swapChainFramebuffers.size;

	VkCommandBufferAllocateInfo allocInfo = {0};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = commandBufferCount;

	VkCommandBuffer commandBufferData[commandBufferCount];
	if (vkAllocateCommandBuffers(device, &allocInfo, commandBufferData) != VK_SUCCESS) {
		error("failed to allocate command buffers!");
	}
	for (int i = 0; i < commandBufferCount; i++) {
		commandBuffers.append(&commandBuffers, commandBufferData[i]);
	}
	info(3, "ALLOCATED COMMAND BUFFERS\n");

	info(3, "RECORDING COMMAND BUFFERS\n");
	for (int i = 0; i < commandBufferCount; i++) {
		VkCommandBufferBeginInfo beginInfo = {0};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0; // Optional
		beginInfo.pInheritanceInfo = NULL; // Optional

		if (vkBeginCommandBuffer(commandBuffers.data[i], &beginInfo) != VK_SUCCESS) {
			error("failed to begin recording command buffer!");
		}
		info(3, "\tBEGIN RECORDING COMMAND BUFFER %d\n", i);

		VkRenderPassBeginInfo renderPassInfo = {0};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = swapChainFramebuffers.data[i];
		renderPassInfo.renderArea.offset = (VkOffset2D) {0, 0};
		renderPassInfo.renderArea.extent = swapChainExtent;

		VkClearValue clearColor;
		clearColor.color.float32[0] = 0.0f;
		clearColor.color.float32[1] = 0.0f;
		clearColor.color.float32[2] = 0.0f;
		clearColor.color.float32[3] = 1.0f;
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers.data[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffers.data[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);


		VkBuffer vertexBuffers[] = {vertexBuffer};
		VkDeviceSize offsets[] = {0};
		vkCmdBindVertexBuffers(commandBuffers.data[i], 0, 1, vertexBuffers, offsets);

		vkCmdDraw(commandBuffers.data[i], vertices.size, 1, 0, 0);
		vkCmdEndRenderPass(commandBuffers.data[i]);
		if (vkEndCommandBuffer(commandBuffers.data[i]) != VK_SUCCESS) {
			error("failed to record command buffer!");
		}
		info(3, "\tEND RECORDING COMMAND BUFFER %d\n", i);
		info(3, "RECORDED COMMAND BUFFER %d\n", i);
	}
	info(3, "CREATED COMMAND BUFFERS\n");
}	// END createCommandBuffers

void createSyncObjects(void) {
	imageAvailableSemaphores.resize(&imageAvailableSemaphores, MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(&renderFinishedSemaphores, MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(&inFlightFences, MAX_FRAMES_IN_FLIGHT);
	imagesInFlight.resize(&imagesInFlight, swapChainImages.size);
	imageAvailableSemaphores.size = 0;
	renderFinishedSemaphores.size = 0;
	inFlightFences.size = 0;
	imagesInFlight.size = 0;
	for (int i = 0; i < imagesInFlight.threshold; i++) {
		imagesInFlight.append(&imagesInFlight, VK_NULL_HANDLE);
	}

	VkSemaphoreCreateInfo semaphoreInfo = {0};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {0};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		VkSemaphore imageAvailableSemaphoreData;
		VkSemaphore renderFinishedSemaphoreData;
		VkFence inFlightFenceData;
		if (vkCreateSemaphore(device, &semaphoreInfo, NULL, &imageAvailableSemaphoreData) != VK_SUCCESS ||
		vkCreateSemaphore(device, &semaphoreInfo, NULL, &renderFinishedSemaphoreData) != VK_SUCCESS ||
		vkCreateFence(device, &fenceInfo, NULL, &inFlightFenceData) != VK_SUCCESS) {
			error("failed to create synchronization objects for frame %d!", i);
		}
		imageAvailableSemaphores.append(&imageAvailableSemaphores, imageAvailableSemaphoreData);
		renderFinishedSemaphores.append(&renderFinishedSemaphores, renderFinishedSemaphoreData);
		inFlightFences.append(&inFlightFences, inFlightFenceData);
	}
}	// END createSyncObjects

void drawFrame(void) {
	vkWaitForFences(device, 1, &inFlightFences.data[currentFrame], VK_TRUE, UINT64_MAX);

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores.data[currentFrame], VK_NULL_HANDLE, &imageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		info(50, "\nFRAME %d", (int)currentFrame);
		recreateSwapChain();
		return;
	} else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		error("failed to acquire swap chain image");
	}

	// Check if a previous frame is using this image (i.e. there is its fence to wait on)
	if (imagesInFlight.data[imageIndex] != VK_NULL_HANDLE) {
		vkWaitForFences(device, 1, &imagesInFlight.data[imageIndex], VK_TRUE, UINT64_MAX);
	}
	// Mark the image as now being in use by this frame
	imagesInFlight.data[imageIndex] = inFlightFences.data[currentFrame];

	VkSubmitInfo submitInfo = {0};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	// specify the semaphore to wait for
	VkSemaphore waitSemaphores[] = {imageAvailableSemaphores.data[currentFrame]};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	// actual command buffers to submit
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers.data[imageIndex];

	VkSemaphore signalSemaphores[] = {renderFinishedSemaphores.data[currentFrame]};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(device, 1, &inFlightFences.data[currentFrame]);

   if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences.data[currentFrame]) != VK_SUCCESS) {
		error("failed to submit draw command buffer!");
   }

	// PRESENTATION
	VkPresentInfoKHR presentInfo = {0};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	// semaphores to wait on
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	// swapchains to present images to
	VkSwapchainKHR swapChains[] = {swapChain};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = NULL; // Optional

	// submits a request to present and image to the swap chain
	result = vkQueuePresentKHR(presentQueue, &presentInfo);
	// printf("%d %d\n", framebufferResized, result);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
		framebufferResized) {
		framebufferResized = false;
		info(50, "\nFRAME %d", (int)currentFrame);
		recreateSwapChain();
	} else if (result != VK_SUCCESS) {
		error("failed to acquire swap chain image");
	}

	currentFrame = (currentFrame+1) % MAX_FRAMES_IN_FLIGHT;
}	// END drawFrame

VkShaderModule createShaderModule(char_vector* code) {
	VkShaderModuleCreateInfo createInfo = {0};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.pNext = NULL;
	createInfo.flags = 0;
	createInfo.codeSize = code->size;
	createInfo.pCode = (const uint32_t*) code->data;

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(device, &createInfo, NULL, &shaderModule) != VK_SUCCESS) {
		error("failed to create shader module!");
	}

	return shaderModule;
}	// END createShaderModule

// CHOOSE COLOR SPACE AND COLOR FORMAT
VkSurfaceFormatKHR chooseSwapSurfaceFormat(VkSurfaceFormatKHR_vector* availableFormats) {
	for (int i = 0; i < availableFormats->size; i++) {
		const VkSurfaceFormatKHR availableFormat = availableFormats->data[i];
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}
	return availableFormats->data[0];
}	// END chooseSwapSurfaceFormat

// CHOOSE SWAP CHAIN PRESENT MODE
VkPresentModeKHR chooseSwapPresentMode(const VkPresentModeKHR_vector* availablePresentModes) {
	for (int i = 0; i < availablePresentModes->size; i++) {
		VkPresentModeKHR availablePresentMode = availablePresentModes->data[i];
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}	// END chooseSwapPresentMode

// SWAP EXTENT
VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities) {
	// swap extent is the resultion of swap chain images
	// swap extent is almost always equal to the window's resolution
	if (capabilities->currentExtent.width != UINT32_MAX) {
		return capabilities->currentExtent;
	} else {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		printf("swap extent %d %d\n", width, height);

		VkExtent2D actualExtent = {
			width,
			height
		};

		actualExtent.width = fmax(capabilities->minImageExtent.width, fmin(capabilities->maxImageExtent.width, actualExtent.width));
		actualExtent.height = fmax(capabilities->minImageExtent.height, fmin(capabilities->maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}	// END chooseSwapExtent

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
	SwapChainSupportDetails details = SwapChainSupportDetails_INIT;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, NULL);

	if (formatCount != 0) {
		info(3, "DEVICE SUPPORTS SURFACE FORMATS\n");
		details.formats->resize(details.formats, formatCount);
		VkSurfaceFormatKHR formatData[formatCount];
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, formatData);
		for (int i = 0; i < formatCount; i++) {
			details.formats->append(details.formats, formatData[i]);
		}
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, NULL);

	if (presentModeCount != 0) {
		info(3, "DEVICE SUPPORTS PRESENT MODES\n");
		details.presentModes->resize(details.presentModes, presentModeCount);
		VkPresentModeKHR presentModeData[presentModeCount];
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, presentModeData);
		for (int i = 0; i < presentModeCount; i++) {
			details.presentModes->append(details.presentModes, presentModeData[i]);
		}
	}
	return details;
}

bool isDeviceSuitable(VkPhysicalDevice device) {
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	// use these to determine favorable devices

	QueueFamilyIndices indices = findQueueFamilies(device);

	bool extensionsSupported = checkDeviceExtensionSupport(device);

	bool swapChainAdequate = false;
	if (extensionsSupported) {
		info(3, "DEVICE SUPPORTS EXTENSIONS\n");
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
		swapChainAdequate = !swapChainSupport.formats->empty && !swapChainSupport.presentModes->empty;
		if (swapChainAdequate) info(3, "DEVICE SUPPORTS SWAPCHAINS ADEQUATELY\n");
	}

	return indices.isComplete(&indices) && extensionsSupported && swapChainAdequate;
}	// END isDeviceSuitable

bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
	uint32_t extensionCount;
	// get available extensions enumerating the device's extensions
	vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);

	// put the device's extensions in a list
	VkExtensionProperties_vector* availableExtensions = VkExtensionProperties_vector_new(2, extensionCount);
	vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, availableExtensions->data);

	string_set* requiredExtensions = string_set_new(2, deviceExtensions.size);
	// put all specified device extensions in a set
	for (int i = 0; i < deviceExtensions.size; i++) {
		requiredExtensions->appendP(requiredExtensions, &deviceExtensions.data[i]);
	}

	// get all already available extensions and remove them from requiredExtensions
	for (int i = 0; i < availableExtensions->size; i++) {
		VkExtensionProperties extension = availableExtensions->data[i];
		// if extension is available, it is not required again
		requiredExtensions->removeByData(requiredExtensions, extension.extensionName);
	}

	// free(requiredExtensions);
	return requiredExtensions->size > 0 ? true : false;
}	// END checkDeviceExtensionSupport

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices = QueueFamilyIndices_INIT; // -1 specifies no devices have been found

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);

	VkQueueFamilyProperties_vector* queueFamilies = VkQueueFamilyProperties_vector_new(2, queueFamilyCount);
	VkQueueFamilyProperties queueFamilyArray[queueFamilyCount];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyArray);
	for (int i = 0; i < queueFamilyCount; i++) {
		queueFamilies->append(queueFamilies, queueFamilyArray[i]);
	}

	for (int i = 0; i < queueFamilies->size; i++) {
		VkQueueFamilyProperties queueFamily = queueFamilies->data[i];
		// GRAPHICS SUPPORT
		// bitwise AND that specifies support for VK_QUEUE_GRAPHICS_BIT
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		// PRESENT SUPPORT
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
		if (presentSupport) {
			indices.presentFamily = i;
		}

		if (indices.isComplete(&indices)) {
			break;
		}
	}

	// free(queueFamilies);
	return indices;
}	// END findQueueFamilies

constCharP_vector* getRequiredExtensions(void) {
	// glfw functions to get required vulkan extensions
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	// object* extensions = new(&constCharP_vector);
	// std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
	constCharP_vector* extensions = constCharP_vector_new(2, glfwExtensionCount);
	for (int i = 0; i < glfwExtensionCount; i++) {
		extensions->append(extensions, glfwExtensions[i]);
	}

	if (enableValidationLayers) {
		extensions->append(extensions, VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	// free(extensions);
	return extensions;
}	// END getRequiredExtensions

bool checkValidationLayerSupport(void) {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, NULL);

	VkLayerProperties availableLayers[layerCount];
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);

	for (int i = 0; i < validationLayers.size; i++) {
		const char* layerName = validationLayers.data[i];
		bool layerFound = false;

		for (int i = 0; i < layerCount; i++) {
			VkLayerProperties layerProperties = availableLayers[i];
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}	// END checkValidationLayerSupport

char_vector* readFile(const char* filename) {
	FILE* file = fopen(filename, "rb");
	long int bufferSize = 0;
	char_vector* buffer = char_vector_new(2, 1);
	if (file == NULL) {
		error("Failed to open file\n");
	} else {
		fseek(file, 0, SEEK_END);
		bufferSize = ftell(file);

		buffer->resize(buffer, bufferSize);
		fseek(file, 0, SEEK_SET);

		for (uint32_t i = 0; i < bufferSize; i++) {
			buffer->append(buffer, fgetc(file));
			// putchar(buffer->data[i]);
		}
		fclose(file);
	}
	return buffer;
}	// END readFile

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {
	fprintf(stderr, "validation layer: %s\n", pCallbackData->pMessage);
	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
			// Message is important enough to show
	}
	return VK_FALSE;
}	// END debugCallback

// #include <gsl/gsl_sf.h>

int main(void) {
	char* locale;

	// #define TEST 50000
	// #define TEST2 100
	// uint32_vector* test[TEST];
	// for (int j = 0; j < TEST2; j++) {
	// 	for (int i = 0; i < TEST; i++) {
	// 		test[i] = uint32_vector_new(2, 1024);
	// 	}
	// 	for (int i = 0; i < TEST; i++) {
	// 		test[i]->free(test[i]);
	// 	}
	// }
	locale = setlocale(LC_ALL, "");
	run();

	printf("FINISHED\n");
	return EXIT_SUCCESS;
}	// END main
