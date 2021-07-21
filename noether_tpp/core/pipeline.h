/**
 * @file pipeline.h
 * @copyright Copyright (c) 2021, Southwest Research Institute
 *
 * @par License
 * Software License Agreement (Apache License)
 * @par
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * @par
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <vector>

#include <pcl/PolygonMesh.h>

#include <noether_tpp/core/mesh_modifier.h>
#include <noether_tpp/core/tool_path_modifier.h>
#include <noether_tpp/core/tool_path_planner.h>
#include <noether_tpp/core/types.h>

namespace noether_tpp
{

/**
 * @brief The ToolPathPlannerPipeline class - Collects together a set of mesh modifiers, a planner,
 * and a set of tool path modifiers. These sub-units then can be called using a single line to
 * pre-process meshes, plan paths, and operate on the paths.
 */
class ToolPathPlannerPipeline
{
public:
std::vector<ToolPaths> plan(pcl::PolygonMesh mesh);

std::vector<MeshModifier> mesh_modifiers;
std::vector<ToolPathPlanner> planner;
std::vector<ToolPathModifier> modifiers;
};

} // namespace noether_tpp
