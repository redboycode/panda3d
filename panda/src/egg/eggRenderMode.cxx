// Filename: eggRenderMode.cxx
// Created by:  drose (20Jan99)
// 
////////////////////////////////////////////////////////////////////

#include "eggRenderMode.h"
#include <indent.h>
#include <string_utils.h>
#include <notify.h>

TypeHandle EggRenderMode::_type_handle;

////////////////////////////////////////////////////////////////////
//     Function: EggRenderMode::write
//       Access: Public
//  Description: Writes the attributes to the indicated output stream in
//               Egg format.
////////////////////////////////////////////////////////////////////
void EggRenderMode::
write(ostream &out, int indent_level) const {
  if (get_alpha_mode() != AM_unspecified) {
    indent(out, indent_level)
      << "<Scalar> alpha { " << get_alpha_mode() << " }\n";
  }
  if (get_depth_write_mode() != DWM_unspecified) {
    indent(out, indent_level)
      << "<Scalar> depth_write { " << get_depth_write_mode() << " }\n";
  }
  if (get_depth_test_mode() != DTM_unspecified) {
    indent(out, indent_level)
      << "<Scalar> depth_test { " << get_depth_test_mode() << " }\n";
  }
  if (has_draw_order()) {
    indent(out, indent_level)
      << "<Scalar> draw-order { " << get_draw_order() << " }\n";
  }
  if (has_bin()) {
    indent(out, indent_level)
      << "<Scalar> bin { " << get_bin() << " }\n";
  }
}

////////////////////////////////////////////////////////////////////
//     Function: EggRenderMode::Equality Operator
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
bool EggRenderMode::
operator == (const EggRenderMode &other) const {
  if (_alpha_mode != other._alpha_mode ||
      _depth_write_mode != other._depth_write_mode ||
      _depth_test_mode != other._depth_test_mode ||
      _has_draw_order != other._has_draw_order) {
    return false;
  }

  if (_has_draw_order) {
    if (_draw_order != other._draw_order) {
      return false;
    }
  }

  if (_bin != other._bin) {
    return false;
  }

  return true;
}

////////////////////////////////////////////////////////////////////
//     Function: EggRenderMode::Ordering Operator
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
bool EggRenderMode::
operator < (const EggRenderMode &other) const {
  if (_alpha_mode != other._alpha_mode) {
    return (int)_alpha_mode < (int)other._alpha_mode;
  }
  if (_depth_write_mode != other._depth_write_mode) {
    return (int)_depth_write_mode < (int)other._depth_write_mode;
  }
  if (_depth_test_mode != other._depth_test_mode) {
    return (int)_depth_test_mode < (int)other._depth_test_mode;
  }

  if (_has_draw_order != other._has_draw_order) {
    return (int)_has_draw_order < (int)other._has_draw_order;
  }

  if (_has_draw_order) {
    if (_draw_order != other._draw_order) {
      return _draw_order < other._draw_order;
    }
  }

  if (_bin != other._bin) {
    return _bin < other._bin;
  }

  return false;
}

////////////////////////////////////////////////////////////////////
//     Function: EggRenderMode::string_alpha_mode
//       Access: Public
//  Description: Returns the AlphaMode value associated with the given
//               string representation, or AM_unspecified if the string
//               does not match any known AlphaMode value.
////////////////////////////////////////////////////////////////////
EggRenderMode::AlphaMode EggRenderMode::
string_alpha_mode(const string &string) {
  if (cmp_nocase_uh(string, "off") == 0) {
    return AM_off;
  } else if (cmp_nocase_uh(string, "on") == 0) {
    return AM_on;
  } else if (cmp_nocase_uh(string, "blend") == 0) {
    return AM_blend;
  } else if (cmp_nocase_uh(string, "blend_no_occlude") == 0) {
    return AM_blend_no_occlude;
  } else if (cmp_nocase_uh(string, "ms") == 0) {
    return AM_ms;
  } else if (cmp_nocase_uh(string, "ms_mask") == 0) {
    return AM_ms_mask;
  } else {
    return AM_unspecified;
  }
}

////////////////////////////////////////////////////////////////////
//     Function: EggRenderMode::string_depth_write_mode
//       Access: Public
//  Description: Returns the DepthWriteMode value associated with the
//               given string representation, or DWM_unspecified if
//               the string does not match any known DepthWriteMode
//               value.
////////////////////////////////////////////////////////////////////
EggRenderMode::DepthWriteMode EggRenderMode::
string_depth_write_mode(const string &string) {
  if (cmp_nocase_uh(string, "off") == 0) {
    return DWM_off;
  } else if (cmp_nocase_uh(string, "on") == 0) {
    return DWM_on;
  } else {
    return DWM_unspecified;
  }
}

////////////////////////////////////////////////////////////////////
//     Function: EggRenderMode::string_depth_test_mode
//       Access: Public
//  Description: Returns the DepthTestMode value associated with the
//               given string representation, or DWM_unspecified if
//               the string does not match any known DepthTestMode
//               value.
////////////////////////////////////////////////////////////////////
EggRenderMode::DepthTestMode EggRenderMode::
string_depth_test_mode(const string &string) {
  if (cmp_nocase_uh(string, "off") == 0) {
    return DTM_off;
  } else if (cmp_nocase_uh(string, "on") == 0) {
    return DTM_on;
  } else {
    return DTM_unspecified;
  }
}


////////////////////////////////////////////////////////////////////
//     Function: AlphaMode output operator
//  Description: 
////////////////////////////////////////////////////////////////////
ostream &operator << (ostream &out, EggRenderMode::AlphaMode mode) {
  switch (mode) {
  case EggRenderMode::AM_unspecified:
    return out << "unspecified";
  case EggRenderMode::AM_off:
    return out << "off";
  case EggRenderMode::AM_on:
    return out << "on";
  case EggRenderMode::AM_blend:
    return out << "blend";
  case EggRenderMode::AM_blend_no_occlude:
    return out << "blend_no_occlude";
  case EggRenderMode::AM_ms:
    return out << "ms";
  case EggRenderMode::AM_ms_mask:
    return out << "ms_mask";
  }

  nassertr(false, out);
  return out << "(**invalid**)";
}

////////////////////////////////////////////////////////////////////
//     Function: DepthWriteMode output operator
//  Description: 
////////////////////////////////////////////////////////////////////
ostream &operator << (ostream &out, EggRenderMode::DepthWriteMode mode) {
  switch (mode) {
  case EggRenderMode::DWM_unspecified:
    return out << "unspecified";
  case EggRenderMode::DWM_off:
    return out << "off";
  case EggRenderMode::DWM_on:
    return out << "on";
  }

  nassertr(false, out);
  return out << "(**invalid**)";
}

////////////////////////////////////////////////////////////////////
//     Function: DepthTestMode output operator
//  Description: 
////////////////////////////////////////////////////////////////////
ostream &operator << (ostream &out, EggRenderMode::DepthTestMode mode) {
  switch (mode) {
  case EggRenderMode::DTM_unspecified:
    return out << "unspecified";
  case EggRenderMode::DTM_off:
    return out << "off";
  case EggRenderMode::DTM_on:
    return out << "on";
  }

  nassertr(false, out);
  return out << "(**invalid**)";
}

    
