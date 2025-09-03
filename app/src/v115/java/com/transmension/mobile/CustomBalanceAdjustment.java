 /*
  * Copyright (C) 2023-2025  PvZ TV Touch Team
  *
  * This file is part of PlantsVsZombies-AndroidTV.
  *
  * PlantsVsZombies-AndroidTV is free software: you can redistribute it and/or
  * modify it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or (at your
  * option) any later version.
  *
  * PlantsVsZombies-AndroidTV is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
  * Public License for more details.
  *
  * You should have received a copy of the GNU General Public License along with
  * PlantsVsZombies-AndroidTV.  If not, see <https://www.gnu.org/licenses/>.
  */

 package com.transmension.mobile;

 import static com.transmension.mobile.Global.globalIsSelected;
 import static com.transmension.mobile.Global.seedName;
 import static com.transmension.mobile.Global.seedNameSelected;

 import android.animation.LayoutTransition;
 import android.animation.ObjectAnimator;
 import android.app.ActionBar;
 import android.app.Activity;
 import android.app.AlertDialog;
 import android.content.Context;
 import android.content.Intent;
 import android.content.SharedPreferences;
 import android.content.res.Configuration;
 import android.graphics.Color;
 import android.graphics.Typeface;
 import android.graphics.drawable.ColorDrawable;
 import android.graphics.drawable.ShapeDrawable;
 import android.graphics.drawable.shapes.RoundRectShape;
 import android.os.Build;
 import android.os.Bundle;
 import android.preference.PreferenceManager;
 import android.transition.Slide;
 import android.util.Xml;
 import android.view.Gravity;
 import android.view.KeyEvent;
 import android.view.View;
 import android.view.Window;
 import android.widget.Button;
 import android.widget.CheckBox;
 import android.widget.LinearLayout;
 import android.widget.NumberPicker;
 import android.widget.ScrollView;
 import android.widget.TableLayout;
 import android.widget.TableRow;
 import android.widget.TextView;
 import android.widget.Toast;

 import com.trans.pvztv.R;

 import org.xmlpull.v1.XmlPullParser;
 import org.xmlpull.v1.XmlPullParserException;

 import java.io.IOException;
 import java.io.InputStream;
 import java.util.Locale;

 public class CustomBalanceAdjustment extends Activity {

     @Override
     protected void onCreate(Bundle savedInstanceState) {
         super.onCreate(savedInstanceState);

         boolean isNight = (getResources().getConfiguration().uiMode & Configuration.UI_MODE_NIGHT_YES) == Configuration.UI_MODE_NIGHT_YES;

         if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH)
             setTheme(isNight ? android.R.style.Theme_DeviceDefault : android.R.style.Theme_DeviceDefault_Light);
         Window window = getWindow();
         if (!isNight) {
             window.getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LIGHT_STATUS_BAR | View.SYSTEM_UI_FLAG_LIGHT_NAVIGATION_BAR);
         }
         if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q)
             window.setNavigationBarContrastEnforced(false);
         if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
             window.setStatusBarColor(Color.TRANSPARENT);
             window.setNavigationBarColor(Color.TRANSPARENT);
         }
         ActionBar actionBar = getActionBar();
         if (actionBar != null) {
             actionBar.setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
         }

         setTitle(getString(R.string.custom_balance_title));
         SharedPreferences sharedPreferences = getSharedPreferences("data", 0);

         ScrollView scrollView = new ScrollView(this);
         LinearLayout linearLayout = new LinearLayout(this);
         TextView intro = new TextView(this);
         intro.setGravity(Gravity.CENTER);
         intro.setText(R.string.addon_custom_balance_adjustment_info);
         intro.setTextSize(20f);

         TableLayout tableLayout = new TableLayout(this);
         tableLayout.setLayoutParams(new TableLayout.LayoutParams(TableLayout.LayoutParams.MATCH_PARENT, TableLayout.LayoutParams.WRAP_CONTENT));
         tableLayout.setStretchAllColumns(false);

         LinearLayout.LayoutParams wrapWrapParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
         wrapWrapParams.gravity = Gravity.CENTER;
         LinearLayout.LayoutParams matchWrapParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
         matchWrapParams.gravity = Gravity.CENTER;
         LinearLayout.LayoutParams weightParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
         weightParams.weight = 1;
         LinearLayout.LayoutParams marginParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
         marginParams.setMargins(0, 20, 0, 20);

         Button seedPicker = new Button(this);
         boolean isSelected = globalIsSelected;
         seedPicker.setText(isSelected ? seedNameSelected : "选择卡片类型");
         seedPicker.setTextSize(17f);
         seedPicker.setOnClickListener(view -> {
             startActivity(new Intent(CustomBalanceAdjustment.this, SeedChooser.class));
             finish();
         });

         LinearLayout balanceChooser = new LinearLayout(this);
         balanceChooser.setOrientation(LinearLayout.HORIZONTAL);

         TextView costInfo = new TextView(this);
         costInfo.setGravity(Gravity.CENTER);
         costInfo.setText("花费");
         costInfo.setTextSize(15f);

         NumberPicker costPicker = new NumberPicker(this);
         costPicker.setFormatter(new NumberPicker.Formatter() {
             @Override
             public String format(int value) {
                 return String.valueOf(value * 25); // 步长25
             }
         });
         costPicker.setMinValue(0);
         costPicker.setMaxValue(12);
         costPicker.setLayoutParams(weightParams);
         costPicker.setValue(sharedPreferences.getInt("cost", 0));

         TextView refreshInfo = new TextView(this);
         refreshInfo.setGravity(Gravity.CENTER);
         refreshInfo.setText("冷却时间");
         refreshInfo.setTextSize(15f);

         NumberPicker refreshPicker = getRefreshPicker();
         refreshPicker.setLayoutParams(weightParams);
         refreshPicker.setValue(sharedPreferences.getInt("refresh", 0));

         balanceChooser.addView(costInfo);
         balanceChooser.addView(costPicker);
         balanceChooser.addView(refreshInfo);
         balanceChooser.addView(refreshPicker);

         Button save = new Button(this);
         save.setText("保存修改");
         save.setTextSize(17f);
         save.setOnClickListener(view -> {
//             sharedPreferences.edit().putInt("cost", costPicker.getValue()).putInt("refresh", refreshPicker.getValue()).putInt("scaleX", scaleSeekBar.getProgress()).putInt("scaleY", scaleSeekBar.getProgress()).putBoolean("shiLiuBiJiu", !fullscreenCheckBox.isChecked()).apply();
//             Toast.makeText(CustomBalanceAdjustment.this, getString(R.string.addon_aspect_toast1) + (fullscreenCheckBox.isChecked() ? getString(R.string.addon_aspect_toast2) : String.format(Locale.getDefault(), "%d: %d", costPicker.getValue(), refreshPicker.getValue())) + String.format(Locale.getDefault(), getString(R.string.addon_aspect_toast3), scaleSeekBar.getProgress()), Toast.LENGTH_SHORT).show();
         });

         linearLayout.setOrientation(LinearLayout.VERTICAL);
         linearLayout.addView(intro);
         linearLayout.addView(tableLayout);
         linearLayout.addView(seedPicker);
         linearLayout.addView(balanceChooser);
         linearLayout.addView(save);
         scrollView.addView(linearLayout);
         setContentView(scrollView);
     }

     private NumberPicker getRefreshPicker() {
         NumberPicker refreshPicker = new NumberPicker(this);
         refreshPicker.setFormatter(value -> {
             switch (value) {
                 case 0:
                     return "短";
                 case 1:
                     return "中等";
                 case 2:
                     return "长";
                 case 3:
                     return "很长";
                 default:
                     return "0";
             }
         });
         refreshPicker.setMinValue(0);
         refreshPicker.setMaxValue(3);
         return refreshPicker;
     }

     @Override
     public boolean onKeyDown(int keyCode, KeyEvent event) {

         return super.onKeyDown(keyCode, event);
     }

     static class MyTextView extends TextView {

         public final int preferenceId;

         public MyTextView(Context context) {
             super(context);
             preferenceId = -1;
         }

         public MyTextView(Context context, int id) {
             super(context);
             preferenceId = id;
         }
     }

 }