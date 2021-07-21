/**
 * @file tool_path_planner.h
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

#include <pcl/PolygonMesh.h>

#include <noether_tpp/core/tool_path_modifier.h>
#include <noether_tpp/core/types.h>

namespace noether_tpp
{

/**
 * @brief The ToolPathPlanner class - generic interface for a planner that operates on a mesh.
 */
class ToolPathPlanner
{
public:
  virtual ToolPaths plan(const pcl::PolygonMesh& mesh) = 0;
};

} // namespac noether_tpp
