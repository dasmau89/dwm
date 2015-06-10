# $Id: PKGBUILD 60970 2011-12-19 21:33:58Z spupykin $
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.0
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'profont')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
		config.h
		dwm.desktop
		dwm-6.0-systray
		dwm-6.0-patchsammlung+systray
		dwm-6.0-patchsammlung
		dwm-and-stuff
)
md5sums=('8bb00d4142259beb11e13473b81c0857'
         'a3a009edd73b401e7908a6b5035f8b8e'
         'cb23306361d4d85d0ae89c7f68ad2c8a'
         '0a527af3bcfbf628ed118bdf86521161'
         '63cef5d635e87be67581469b13e7c70f'
         '799e7f4979fe081d2b73cf0d255d3ac7'
		'6c1d39c01638d2b4e9df9f19d6128962'
)
build() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  cp $srcdir/dwm-6.0-patchsammlung+systray .
  cp $srcdir/dwm-6.0-patchsammlung .
  #cp $srcdir/dwm-6.0-systray .
  patch -p1 < dwm-6.0-patchsammlung
#patch -p1 < dwm-6.0-patchsammlung+systray
#  patch -p1 < dwm-6.0-systray
  sed -i 's/CPPFLAGS =/CPPFLAGS +=/g' config.mk
  sed -i 's/^CFLAGS = -g/#CFLAGS += -g/g' config.mk
  sed -i 's/^#CFLAGS = -std/CFLAGS += -std/g' config.mk
  sed -i 's/^LDFLAGS = -g/#LDFLAGS += -g/g' config.mk
  sed -i 's/^#LDFLAGS = -s/LDFLAGS += -s/g' config.mk
  make clean
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
  install -m755 -D $srcdir/dwm-and-stuff $pkgdir/usr/bin/dwm-and-stuff
}
