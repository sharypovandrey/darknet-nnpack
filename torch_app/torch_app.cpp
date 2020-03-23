#include <torch/script.h> // One-stop header.

#include <iostream>
#include <memory>

int main(int argc, const char* argv[]) {

  // cv::cvtColor(frame, frame, CV_BGR2RGB);
  // frame.convertTo(frame, CV_32FC3, 1.0f / 255.0f);
  // auto input_tensor = torch::from_blob(frame.data, {1, frame_h, frame_w, kCHANNELS});
  // input_tensor = input_tensor.permute({0, 3, 1, 2});

  // torch::jit::script::Module module;
  torch::jit::script::Module head_model;
  torch::jit::script::Module tail_model;
  try {
    // Deserialize the ScriptModule from a file using torch::jit::load().
    // module = torch::jit::load("/home/andrey/Github/darknet-nnpack/src/traced_resnet_model.pt");
    head_model = torch::jit::load("/home/andrey/Github/darknet-nnpack/torch_app/traced_head.pt");
    tail_model = torch::jit::load("/home/andrey/Github/darknet-nnpack/torch_app/traced_tail.pt");
  }
  catch (const c10::Error& e) {
    std::cerr << "error loading the model\n";
    return -1;
  }

  std::cout << "model is loaded ok\n";


  // auto modules = module.named_modules(); 
  // c10::optional<torch::jit::script::Method> method = module.find_method("forward_one");

  // Create a vector of inputs.
  std::vector<torch::IValue> anchor_input;
  anchor_input.push_back(torch::ones({1, 3, 64, 64}));

  std::vector<torch::IValue> current_input;
  current_input.push_back(torch::ones({1, 3, 64, 64}));

  at::Tensor anchor_encoder = head_model.forward(anchor_input).toTensor();
  at::Tensor current_encoder = head_model.forward(current_input).toTensor();

  at::Tensor distance = torch::abs(torch::sub(anchor_encoder, current_encoder));

  std::vector<torch::IValue> iv_distance;
  std::cout << distance[0][0].item().to<float>() << '\n';
  torch::IValue encoder = distance.toTensorList(); 
  iv_distance.push_back(encoder);
  at::Tensor y = tail_model.forward(iv_distance).toTensor();
  y = torch::sigmoid(y);
  float out = y[0].item().to<float>();
  std::cout << out << '\n';
  
  if (out > 0.5)
  {
    std::cout << "matched" << '\n';
  } else {
    std::cout << "not matched" << '\n';
  };

  // Execute the model and turn its output into a tensor.
  // at::Tensor output = module.forward(inputs).toTensor();
  // std::cout << output.slice(/*dim=*/1, /*start=*/0, /*end=*/5) << '\n';

}